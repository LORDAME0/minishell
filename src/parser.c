/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:39:59 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/14 03:25:22 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
		if ((ft_strncmp(line, delimiter, ft_strlen (delimiter)) == 0
				&& ft_strlen(delimiter) == ft_strlen(line)))
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

static void	eval_io(t_seq *seq, char *rederiction_type, char *file)
{
	panic(rederiction_type == NULL || file == NULL, "NULL PARAM", __func__);
	if (rederiction_type[0] == '<')
	{
		safe_close(seq->in, 0);
		if (rederiction_type[1])
			seq->in = heredoc(file);
		else
			seq->in = open (file, O_RDONLY);
		if (seq->in == -1)
			perror("Error :");
	}
	else
	{
		safe_close(seq->out, 1);
		if (rederiction_type[1])
			seq->out = open (file, O_APPEND | O_WRONLY | O_CREAT, 0777);
		else
			seq->out = open (file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (seq->out == -1)
			perror("Error :");
	}
}

static t_token	*eval_redirection(t_seq *seq, t_token *token)
{
	char	*rederiction_type;

	rederiction_type = token->elem;
	token = token->next;
	eval_io(seq, rederiction_type, token->elem);
	if (seq->in < 0 || seq->out < 0)
	{
		while (token && token->type != pip)
			token = token->next;
		free_2d_array(seq->args);
		seq->args = NULL;
	}
	return (token);
}

static void	eval_pipes(t_seq *seq)
{
	bool		first;
	bool		last;
	int			fd[2];

	first = true;
	last = false;
	while (seq)
	{
		if (first == false)
		{
			safe_close(seq->in, 0);
			seq->in = fd[0];
		}
		if (last == false)
		{
			safe_close(seq->out, 1);
			pipe(fd);
			seq->out = fd[1];
			first = false;
		}
		seq = seq->next;
		if (seq && seq->next == NULL)
			last = true;
	}
}

t_seq	*parser(t_token *list)
{
	t_seq	*head;
	t_seq	*tmp;

	head = NULL;
	while (list)
	{
		tmp = create_seq(init_2d_array(), 0, 1);
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
	}
	if (head && head->next)
		eval_pipes(head);
	return (head);
}
// #ifdef DEBUG
	// print_seq(head);
// #endif
// void	print_seq(t_seq *seq)
// {
	// int	i;
//
	// i = 1;
	// if (seq == NULL)
		// return ;
	// while (seq)
	// {
		// if (seq->args)
		// {
			// printf ("CMD :: %s\n", seq->args[0]);
			// if (seq->args[1])
			// {
				// while (seq->args[i])
				// {
					// printf ("ARG[%d] :: %s\n", i, seq->args[i]);
					// i++;
				// }
				// i = 0;
			// }
		// }
		// else
			// printf ("CMD :: %s\n", NULL);
		// printf ("IN :: %d\n", seq->in);
		// printf ("OUT :: %d\n", seq->out);
		// seq = seq->next;
	// }
// }
