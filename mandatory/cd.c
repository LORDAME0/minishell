/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:40:34 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/12 21:10:43 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_env	*find_key(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp((env)->key, key, ft_strlen(key)) == 0
			&& (ft_strlen(key) == ft_strlen(env->key)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	update_paths_env(t_env **env)
{
	t_env		*pwd;
	t_env		*opwd;
	char		cwd[PATH_MAX];

	pwd = find_key(*env, "PWD");
	if (pwd == NULL)
		add_variable_back(env,
			create_variable("PWD", ft_strdup(getcwd(cwd, sizeof(cwd)))));
  	else
  	{
		opwd = find_key(*env, "OLDPWD");
		if (opwd == NULL)
			add_variable_back(env, create_variable("OLDPWD", pwd->value)); 
		else
		{
			free(opwd->value);
			opwd->value = pwd->value;
		}
		pwd->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
  	}
}

static int	cd_home(t_env	**env)
{
	char	*user;
	char	*home_path;

	user = find_value(*env, "USER");
	home_path = ft_strjoin("/Users/", user);
	if (chdir(home_path))
		goto error;
	else
		update_paths_env(env);
	free(home_path);
	return (0);
	error:
	free(home_path);
	perror("Error ");
	return (1);
}

#include <sys/stat.h>

int	bcd(char *path, t_env **env)
{
	char				cwd[PATH_MAX];


	if (path == NULL)
		return (cd_home(env));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Error : ");
		cd_home(env);
		return (-1);
	}
	else
	{
		if (chdir(path))
		{
			perror("Error : ");
			return (1);
		}
		else
			update_paths_env(env);
	}
	return (0);
}
