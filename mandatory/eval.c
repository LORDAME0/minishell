/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:13:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/08 21:29:44 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <unistd.h>

char *find_in_path(char *cmd, char **env)
{
	char **paths = ft_split(ft_split(env[find_in_2d_array(env, "PATH=")], '=')[1], ':');
	int		i;

	ft_assert(env == NULL, "NULL ENV", __func__);
	ft_assert(env == NULL, "NULL CMD", __func__);
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
	cmd = ft_strjoin(ft_split(env[find_in_2d_array(env, "PWD=")], '=')[1], cmd);
	printf ("cmd :: %s\n", cmd);
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
		if (execve(cmd, seq->args, env) == -1)
			printf ("MINIShell : command not found\n");
	}
	if (seq->in != 0)
		close (seq->in);
	if (seq->out != 1)
		close (seq->out);
	return (pid);
}

enum builtins {becho, benv, bexport, bunset, bcd, bpwd, bexit};

int	is_builtin(char *cmd)
{
	ft_assert (cmd == NULL, "PARAM IS NULL", __func__);
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (becho);
	if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (benv);
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (bexport);
	if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (bunset);
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (bcd);
	if (ft_strncmp(cmd, "pwq", ft_strlen(cmd)) == 0)
		return (bpwd);
	if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (bexit);
	return (-1);
}

void	exec_builtin(t_seq *seq, int builtin)
{
	if (builtin == becho)
		echo(seq->args + 1, seq->out);
	if (builtin == bcd)
		cd(seq->args[1], NULL);
	if (builtin == bexit && seq->next == NULL && seq->num == 1)
		exit (0);
	if (seq->in != 0)
		close (seq->in);
	if (seq->out != 1)
		close (seq->out);
}

void	eval_seq(t_seq *list, char **env)
{
	t_seq	*tmp;
	int		builtin;

	tmp = list;
	while (list)
	{
		builtin = is_builtin(list->args[0]);
		if (builtin != -1)
			exec_builtin(list, builtin);
		else
			waitpid(ft_exec(find_in_path(list->args[0], env), list, env),
					&g_global.last_return, 0);
		list = list->next;
	}
	/* free_seq(tmp); */
}
