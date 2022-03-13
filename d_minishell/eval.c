/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:13:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/13 09:45:28 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	**ft_split_paths(char **env)
{
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
	return (paths);
}


static char	*find_in_path(char *cmd, char **env)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**paths;

	i = 0;
	panic(env == NULL, "NULL CMD", __func__);
	if (access(cmd, X_OK) == 0)
		return cmd;
	panic(env == NULL, "NULL ENV", __func__);
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
			return (tmp2);
		}
		else
			free(tmp2);
		i++;
	}
	g_last_return = 127;
	printf ("MINIShell : command not found\n");
	free(tmp);
	free_2d_array(paths);
	return (cmd); 
}

static pid_t	ft_exec(char *cmd, t_seq *seq, char **env, t_env **denv)
{
	pid_t	pid;
	int	builtin;

	errno = 0;
	pid = fork();
	if (pid == 0)
	{
    dup2(seq->in, 0);
    dup2(seq->out, 1);
	 if (seq && seq->args && seq->args[0])
	 {
		 builtin = is_builtin(seq->args[0]);
		 if (builtin != -1)
			exec_builtin(denv, seq, builtin);
		 else
		 {
			cmd = find_in_path(cmd, env);
			if (execve(cmd, seq->args, env) == -1)
				exit (127);
		 }
	 }
	 exit (0);
	}
	if (seq->in != 0)
		close (seq->in);
	if (seq->out != 1)
		close (seq->out);
	return (pid);
}

static void	complex_cmd(t_seq *list, t_env **denv)
{
	int	i;
	int	j;
	char	**env;
	pid_t	pid[PID_BUFFER_SIZE];

	i = 0;
	j = 0;
	env = t_env_to_2d_array(*denv);
	while (list)
	{
		if (list->args != NULL)
			pid[i++] = ft_exec(list->args[0], list, env, denv);
		list = list->next;
	}
	while (j < i)
		waitpid(pid[j++], &g_last_return, 0);
	if (g_last_return != 127)
		g_last_return = WEXITSTATUS(g_last_return);
	free_2d_array(env);
}

void	eval_seq(t_seq *list, t_env	**denv)
{
	g_last_return = 0;
	if (denv == NULL)
	{
		printf ("MINIShell :: set environment\n");
		exit(1);
	}
	if (list == NULL)
		return ;
	if (list && list->args && list->args[0]
		&& list->next == NULL
		&& is_builtin(list->args[0]) != -1)
		exec_builtin(denv, list, is_builtin(list->args[0]));
	else if (list)
		complex_cmd(list, denv);
}
