/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:40:34 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/09 14:49:00 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/* static	void	update_paths_env(char **env) */
/* { */
/* 	int		old_index; */
/* 	int		current_index; */
/* 	char	*current_dir; */

/* 	old_index = find_in_2d_array(env, "OLDPWD"); */
/* 	current_index = find_in_2d_array(env, "PWD"); */
/* 	if (old_index == -1 || current_index == -1) */
/* 		printf ("Error : env is corrupt\n"); */
/* 	free(env[old_index]); */
/* 	env[old_index] = ft_strjoin("OLD", env[current_index]); */
/* 	free(env[current_index]); */
/* 	current_dir = return_current_dir(); */
/* 	env[current_index] = ft_strjoin("PWD=", current_dir); */
/* 	free(current_dir); */
/* } */

static	int	cd_home(t_env	*env)
{
	char	*user;
	char	*home_path;

	(void)env;
	user = getenv("USER");
	home_path = ft_strjoin("/Users/", user);
	if (chdir(home_path))
	{
		perror("Error ");
		return (1);
	}
	/* else */
	/* 	update_paths_env(env); */
	return (0);
}

int	cd(char *path, t_env *env)
{
	(void)env;
	if (path == NULL)
		return (cd_home(env));
	else
	{
		if (chdir(path))
		{
			perror("Error ");
			return (1);
		}
		/* else */
		/* 	update_paths_env(env); */
	}
	return (0);
}
