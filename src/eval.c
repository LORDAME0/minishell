/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:13:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/27 12:24:12 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stddef.h>

static pid_t	exec_cmd(char *cmd, t_seq *seq, char **env, t_env **denv)
{
	pid_t	pid;
	int		builtin;

	pid = fork();
	if (pid == 0)
	{
		if (seq && seq->args && seq->args[0])
		{
			builtin = is_builtin(seq->args[0]);
			if (builtin != -1)
				exec_builtin(denv, seq, builtin);
			else
			{
				cmd = find_in_path(cmd, env);
				dup2(seq->in, 0);
				dup2(seq->out, 1);
				if (execve(cmd, seq->args, env) == -1)
					exit (127);
			}
		}
		exit (0);
	}
	safe_close(seq->in);
	safe_close(seq->out);
	return (pid);
}

static void	complex_cmd(t_seq *list, t_env **denv)
{
	int		i;
	int		j;
	char	**env;
	pid_t	*pid;

	i = 0;
	j = 0;
	env = t_env_to_2d_array(*denv);
	pid = malloc(sizeof(t_seq) * seq_size(list));
	if (pid == NULL)
		perror_exit();
	while (list)
	{
		if (list->args != NULL)
			pid[i++] = exec_cmd(list->args[0], list, env, denv);
		else
			safe_close_2(list->in, list->out);
		list = list->next;
	}
	while (j < i)
		waitpid(pid[j++], &g_last_return, 0);
	if (g_last_return != 127)
		g_last_return = WEXITSTATUS(g_last_return);
	free_2d_array(env);
	free(pid);
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
