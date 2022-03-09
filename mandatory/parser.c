/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:39:59 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/09 22:53:16 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_seq(t_seq *seq)
{
	t_seq	*tmp;

	while (seq)
	{
		tmp = seq->next;
		free_2d_array(seq->args);
		free(seq);
		if (seq->in != 0)
			close (seq->in);
		if (seq->out != 1)
			close (seq->out);
		seq = tmp;
	}
}

static t_seq	*create_seq(char **args, int in, int out, int num)
{
	t_seq	*seq;

	ft_assert(args == NULL, "NULL PARAM", __func__);	
	seq = malloc (sizeof(t_seq));
	if (seq == NULL)
	{
		perror ("Error\n");
		exit (1);
	}
	seq->args = args;
	seq->in = in;
	seq->out = out;
	seq->num = num;
	seq->next = NULL;
	return (seq);
}

static t_seq	*get_last_seq(t_seq *seq)
{
	if (seq == NULL)
		return (NULL);
	while (seq->next)
		seq = seq->next;
	return (seq);
}

static void	add_seq_back(t_seq **list, t_seq *new_seq)
{
	ft_assert(new_seq == NULL, "NULL PARAM", __func__);	
	if (*list == NULL)
		*list = new_seq;
	else
		(get_last_seq(*list))->next = new_seq;
}

void	print_seq(t_seq *seq)
{
	int i;

	i = 1;
	if (seq == NULL)
		return ;
	while (seq)
	{
		if (seq->args)
		{
			printf ("CMD :: %s\n", seq->args[0]);
			if (seq->args[1])
			{
				while (seq->args[i])
				{
					printf ("ARG[%d] :: %s\n", i, seq->args[i]);
					i++;
				}
				i = 0;
			}
		}
		else
			printf ("CMD :: %s\n", NULL);
		printf ("IN :: %d\n", seq->in);
		printf ("OUT :: %d\n", seq->out);
		seq = seq->next;
	}
}

static void	eval_out_redirection(t_seq *seq, char *rederiction_type, char *file)
{
	BEGIN
	int	fd;
	ft_assert(rederiction_type == NULL || file == NULL, "NULL PARAM", __func__);

	if (rederiction_type[0] == '>')
	{
		if (seq->out != 1)
			close (seq->out);
		if (rederiction_type[1])
			fd = open (file, O_APPEND | O_WRONLY | O_CREAT, 0777);
		else
			fd = open (file, O_WRONLY | O_TRUNC | O_CREAT,  0777);
		if (fd == -1)
			perror("Error :");
		seq->out = fd;
	}
	END
}

static int	heredoc(char *delimiter)
{
	char	*total;
	char	*line;
	int		fd[2];

	pipe (fd);
	total = ft_strdup("");
	while (1)
	{
		line = readline("heredoc> ");
		if ((ft_strncmp(line, delimiter, ft_strlen (delimiter))  == 0
			&&  ft_strlen(delimiter) == ft_strlen(line)))
			break ;
		total = ft_strjoin_free(total, line);
		total = ft_strjoin_free(total, "\n");
		free(line);
	}
	write (fd[1], total, ft_strlen(total));	
	free(total);
	close (fd[1]);
	return (fd[0]);
}

static void	eval_in_redirection(t_seq *seq, char *rederiction_type, char *file)
{
	BEGIN
	int	fd;

	ft_assert(rederiction_type == NULL || file == NULL, "NULL PARAM", __func__);
	if (rederiction_type[0] == '<')
	{
		if (seq->in != 0)
			close (seq->in);
		if (rederiction_type[1])
			fd = heredoc(file);
		else
			fd = open (file, O_RDONLY);
		if (fd == -1)
			perror("Error :");
		seq->in = fd;
	}
	END
}

static t_token	*eval_redirection(t_seq *seq, t_token *token)
{
	BEGIN
	char	*rederiction_type;
	
	rederiction_type = token->elem;
	token = token->next;
	eval_out_redirection(seq, rederiction_type, token->elem);
	eval_in_redirection(seq, rederiction_type, token->elem);
	if (seq->in < 0 || seq->out < 0)
	{
		while (token && token->type != pip)
			token = token->next;
		free_2d_array(seq->args);
		seq->args = NULL;
	}
	END
	return (token);
}

static void	eval_pipes(t_seq *seq)
{
	int		fd[2];
	bool	first;
	bool	last;

	first = true;
	last = false;
	ft_assert(seq == NULL, "NULL PARAM", __func__);
	if (seq->next)
	{
		while (seq)
		{
			if (first == false)
			{
				if (seq->in != 0)
					close (seq->in);
				seq->in = fd[0];
			}
			if (last == false)
			{
				if (seq->out != 1)
					close(seq->out);
				pipe(fd);
				seq->out = fd[1];
				first = false;
			}
			seq = seq->next;
			if (seq && seq->next == NULL)
				last = true;
		}
	}
}

t_seq	*parser(t_token *list)
{
	BEGIN
	size_t	num;
	t_seq	*head;
	t_seq	*tmp;

	num = 0;
	head = NULL;
	while (list)
	{
		tmp = create_seq(init_2d_array(), 0, 1, num);
		while (list && list->type != pip)
		{
			if (list->type == redirection)
				list = eval_redirection(tmp, list);
			else
				tmp->args = add_element_2d_array_last(tmp->args,
							ft_strdup(list->elem));
			if (list)
				list = list->next;
		}
		if (list && list->type == pip)
			list = list->next;
		add_seq_back(&head, tmp);
		num++;
	}
	eval_pipes(head);
#ifdef DEBUG
	print_seq(head);
#endif
	END
	return (head);
}
