/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:40:34 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/27 11:56:22 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	update_paths_env(t_env **env)
{
	t_env		*pwd;
	t_env		*opwd;
	char		cwd[PATH_MAX];

	pwd = find_key(*env, "PWD");
	if (pwd == NULL)
		add_variable_back(env,
			create_variable(ft_strdup("PWD"),
				ft_strdup(getcwd(cwd, sizeof(cwd)))));
	else
	{
		opwd = find_key(*env, "OLDPWD");
		if (opwd == NULL && pwd != NULL)
			add_variable_back(env,
				create_variable(ft_strdup("OLDPWD"), pwd->value));
		else
		{
			free(opwd->value);
			opwd->value = pwd->value;
		}
		pwd->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
	}
}

static void	cd_home(t_env	**env)
{
	char	*home_path;

	home_path = find_value(*env, "HOME");
	if (home_path == NULL)
		printf ("MINIShell :: home is not set\n");
	else if (chdir(home_path))
		perror("Error ");
	else
		update_paths_env(env);
}

void	bcd(char *path, t_env **env)
{
	char	cwd[PATH_MAX];

	if (path == NULL)
		cd_home(env);
	else if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Error ");
		cd_home(env);
	}
	else
	{
		if (chdir(path))
			perror("Error ");
		else
			update_paths_env(env);
	}
}
