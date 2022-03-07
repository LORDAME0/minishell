/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:39:59 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/07 20:17:37 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <fcntl.h>

void	free_seq(t_seq *seq)
{
	t_seq	*tmp;

	while (seq)
	{
		tmp = seq->next;
		/* free_2d_array(seq->args); */
		free(seq);
		if (seq->in != 0)
			close (seq->in);
		if (seq->out != 1)
			close (seq->out);
		seq = tmp;
	}
}

t_seq	*create_seq(char **args, int in, int out)
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
	seq->next = NULL;
	return (seq);
}

t_seq	*get_last_seq(t_seq *seq)
{
	if (seq == NULL)
		return (NULL);
	while (seq->next)
		seq = seq->next;
	return (seq);
}

void	add_seq_back(t_seq **list, t_seq *new_seq)
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
			printf ("IN :: %d\n", seq->in);
			printf ("OUT :: %d\n", seq->out);
		}
		seq = seq->next;
	}
}

int	eval_out_redirection(char *rederiction_type, char *file)
{
	int	fd;
	ft_assert(rederiction_type == NULL || file == NULL, "NULL PARAM", __func__);

	if (rederiction_type[1])
		fd = open (file, O_APPEND | O_WRONLY | O_CREAT, 0777);
	else
		fd = open (file, O_WRONLY | O_CREAT,  0777);
	if (fd == -1)
		perror("Error :");
	return (fd);
}

int	eval_in_redirection(char *rederiction_type, char *file)
{
	ft_assert(true, "TO_DO", __func__);
	return (0);
}

t_seq	*parser(t_token *list)
{
	int		fd[2];
	int		in;
	int		out;
	t_seq	*seq;
	char	*rederiction_type;
	char	**args;

	out = 1;
	in = 0;
	seq = NULL;
	args = NULL;
	rederiction_type = NULL;
	ft_assert(list == NULL, "NULL PARAM", __func__);	
	while (list)
	{
		args = init_2d_array();
		while (list && list->type != pip)
		{
			if (list->type == redirection)
				rederiction_type = list->elem;
			else if (rederiction_type && rederiction_type[0] == '>')
			{
				if (out != 1)
					close (out);
				out = eval_out_redirection(rederiction_type, list->elem);
				rederiction_type = NULL;
			}
			else if (rederiction_type && rederiction_type[0] == '<')
			{
				ft_assert(true, "IN not implemented yet", __func__);
				/* in = eval_in_redirection(rederiction_type, list->elem); */
				rederiction_type = NULL;
			}
			else if (list->type != redirection && rederiction_type == NULL)
				args = add_element_2d_array_last(args, list->elem);
			list = list->next;
		}
		if (seq && in == 0)
			in = fd[0];
		else
			close(fd[0]);
		if (list && out == 1)
		{
			pipe(fd);
			out = fd[1];
		}
		if (args && args[0])
			add_seq_back(&seq, create_seq(args, in, out));
		else
			free (args);
		out = 1;
		in = 0;
		args = NULL;
		if (list && list->type == pip)
			list = list->next;
	}
	/* if (seq) */
	/* 	print_seq(seq); */
	return (seq);
}
