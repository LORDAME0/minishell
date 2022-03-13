/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                               :e      +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:37:11 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/12 22:41:36 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*prompt(t_env *env)
{
	size_t	i;
	char		*user;
	char		*home_path;
	char		*cwd_ptr;
	char		**cwd_args;
	char		cwd[PATH_MAX];

	i = 0;
	panic(env == NULL, "MINIShell :: set environment", __func__);
	user = find_value(env, "USER");
	if (user)
	{
		cwd_ptr = getcwd(cwd, sizeof(cwd));
		if (cwd_ptr != NULL)
		{
			home_path = ft_strjoin("/Users/", user);
			if (is_equal_str(home_path, cwd))
				return (" ➦  ~ : ");
			if (cwd[0] == '/' && cwd[1] == '\0')
				return (" ➦  / : ");
			if (cwd_ptr != NULL)
			{
				cwd_args = ft_split(cwd, '/');
				while (cwd_args && cwd_args[i] && cwd_args[i + 1])
					i++;
				return (ft_strjoin(ft_strjoin(" ➦  ", cwd_args[i]), " : "));
			}
		}
	}
	return (" ➦  ? : ");
}

void	shell_loop(t_env **denv)
{
	t_seq		*seq;
	char		*line;


	while (1337)
	{
		line = readline(prompt(*denv));
		if (line == NULL)
			bexit(NULL, *denv);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (ft_strncmp("exit", line, ft_strlen(line)) == 0)
		{
			free (line);
			return ;
		}
		ft_add_history(line);
		seq = parsing(line, *denv);
		eval_seq(seq, denv);
		free(line);
		free_seq(seq);
		seq = NULL;
		line = NULL;
	}
}
