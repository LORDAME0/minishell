/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:13:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/07 16:32:25 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/* char *find_in_path(char **env) */
/* { */
/* 	return env[find_in_2d_array(env, "PATH=")]; */ 
/* } */

void	ft_exec(t_seq *seq, char **env)
{
	pid_t	pid;

	errno = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(seq->in, 0);
		dup2(seq->out, 1);
		if (execve(seq->args[0], seq->args, env) == -1)
			perror("Error :");
	}
	if (seq->in != 1)
		close (seq->in);
	if (seq->out != 1)
		close (seq->out);
	wait (NULL);
}

void	eval_seq(t_seq *list, char **env)
{
	t_seq	*tmp;

	tmp = list;
	while (list)
	{
		ft_exec(list, env);
		list = list->next;
	}
	/* free_seq(tmp); */
}
