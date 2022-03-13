/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:52:35 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/13 22:51:57 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_env	*remove_variable(t_env *env, char *variable)
{
	t_env	*tmp;
	t_env	*new_env;

	new_env = NULL;
	while (env)
	{
		tmp = env->next;
		env->next = NULL;
		if (is_equal_str(variable, env->key))
		{
			free(env->key);
			free(env->value);
			free(env);
		}
		else
			add_variable_back(&new_env, env);
		env = tmp;
	}
	return (new_env);
}

void	bunset(char **args, t_env **env)
{
	size_t	i;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i])
	{
		if (find_key(*env, args[i]))
			*env = remove_variable(*env, args[i]);
		i++;
	}
}
