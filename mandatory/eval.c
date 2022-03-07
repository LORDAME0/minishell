/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:13:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/07 19:12:41 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <unistd.h>

char *find_in_path(char *cmd,char **env)
{
	ft_assert(env == NULL, "NULL ENV", __func__);
	ft_assert(env == NULL, "NULL CMD", __func__);
	char **paths = ft_split(ft_split(env[find_in_2d_array(env, "PATH=")], '=')[1], ':');
	int		i;

	/* printf ("***************\n"); */
	/* print_2d_array(paths, 1); */
	/* printf ("***************\n"); */
	i = 0;
	if (paths == NULL)
		return (cmd);
	cmd = ft_strjoin("/", cmd);
	while (paths[i])
	{
		/* printf (" ****** %s\n", ft_strjoin(paths[i], cmd)); */
		if (access(ft_strjoin(paths[i], cmd), X_OK) == 0)
		{
			/* printf ("string :: %s\n", ft_strjoin(paths[i], cmd)); */
			return (ft_strjoin(paths[i], cmd));
		}
		i++;
	}
	return (cmd); 
}

pid_t	ft_exec(char *cmd, t_seq *seq, char **env)
{
	pid_t	pid;

	errno = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(seq->in, 0);
		dup2(seq->out, 1);
		if (execve(cmd, seq->args, NULL) == -1)
			perror("Error :");
	}
	if (seq->in != 1)
		close (seq->in);
	if (seq->out != 1)
		close (seq->out);
	return (pid);
}

void	eval_seq(t_seq *list, char **env)
{
	t_seq	*tmp;

	tmp = list;
	while (list)
	{
		waitpid(ft_exec(find_in_path(list->args[0], env), list, env), NULL, 0);
		list = list->next;
	}
	/* free_seq(tmp); */
}
