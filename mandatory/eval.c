/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:13:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/09 23:03:06 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <unistd.h>

/* char	*pwd_value(char **env) */
/* { */
/* 	char	**key_value; */

/* 	key_value = ft_split(env[find_in_2d_array(env, "PWD=")], '='); */
/* 	free(key_value[0]); */
/* 	return (key_value[1]); */
/* } */

char	**ft_split_paths(char **env)
{
	BEGIN
	char	**paths;
	char	**path_key_value;
	
	if (env == NULL)
	{
		printf ("MINIShell :: set environment\n");
		exit(1);
	}
	path_key_value = ft_split(env[find_in_2d_array(env, "PATH=")], '=');
	paths = ft_split(path_key_value[1], ':');
	free(path_key_value[0]);
	free(path_key_value[1]);
	END
	return (paths);
}


char *find_in_path(char *cmd, char **env)
{
	BEGIN
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**paths;

	i = 0;
	ft_assert(env == NULL, "NULL CMD", __func__);
	if (access(cmd, X_OK) == 0)
		return cmd;
	ft_assert(env == NULL, "NULL ENV", __func__);
	paths = ft_split_paths(env);
	if (paths == NULL)
		return (cmd);
	tmp = ft_strjoin("/", cmd);
	while (paths[i])
	{
		tmp2 = ft_strjoin(paths[i], tmp);
		if (access(tmp2, X_OK) == 0)
		{
			free(tmp);
			free_2d_array(paths);
			END
			return (tmp2);
		}
		else
			free(tmp2);
		i++;
	}
	free(tmp);
	free_2d_array(paths);
	END
	return (cmd); 
}

pid_t	ft_exec(char *cmd, t_seq *seq, char **env)
{
	BEGIN
	pid_t	pid;

	errno = 0;
	pid = fork();
	if (pid == 0)
	{
		cmd = find_in_path(cmd, env);
		dup2(seq->in, 0);
		dup2(seq->out, 1);
		if (execve(cmd, seq->args, env) == -1)
			printf ("MINIShell : command not found\n");
	}
	if (seq->in != 0)
		close (seq->in);
	if (seq->out != 1)
		close (seq->out);
	END
	return (pid);
}

enum e_builtins {becho, benv, bexport, bunset, bcd, bpwd, bexit};

int	is_builtin(char *cmd)
{
	BEGIN
	ft_assert (cmd == NULL, "PARAM IS NULL", __func__);
	END
	if (ft_strncmp(cmd, "echo", 4) == 0)
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
	BEGIN
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
	END
}

void	eval_seq(t_seq *list, t_env	*denv)
{
	BEGIN
	t_seq	*tmp;
	char	**env;
	int		builtin;

	if (denv == NULL)
	{
		printf ("MINIShell :: set environment\n");
		exit(1);
	}
	tmp = list;
	env = t_env_to_char_pp(denv);
	while (list)
	{
		if (list->args == NULL)
		{
			if (list->in != 0)
				close (list->in);
			if (list->out != 1)
				close (list->out);
		}
		else
		{
			builtin = is_builtin(list->args[0]);
			if (builtin != -1)
				exec_builtin(list, builtin);
			else
			{
				printf ("RETURN ::: %d\n", g_global.last_return);
				waitpid(ft_exec(list->args[0], list, env),
						&g_global.last_return, 0);
				g_global.last_return = WEXITSTATUS(g_global.last_return);
				printf ("RETURN ::: %d\n", g_global.last_return);
			}
		}
		list = list->next;
	}
	free_2d_array(env);
	END
}
