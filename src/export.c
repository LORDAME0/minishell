/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:45:05 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/14 01:53:38 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	is_valid_key(char *key)
{
	size_t	i;

	i = 1;
	panic(key == NULL, "key is NULL", __func__);
	if (key[0] == '\0'
		|| (ft_isalpha(key[0]) == 0
			&& key[0] != '_'))
		return (false);
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	add_key(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = find_key(*env, key);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
	}
	else
		add_variable_back(env,
			create_variable(ft_strdup(key), ft_strdup(value)));
}

void	bexport(char **args, t_env **env, int fd)
{
	char	*tmp;
	size_t	i;
	bool	error;

	i = 0;
	error = false;
	if (*args == NULL)
		benv(*env, fd);
	while (args[i])
	{
		tmp = ft_strchr(args[i], '=');
		if (tmp)
			tmp[0] = '\0';
		if (is_valid_key(args[i]) && tmp)
			add_key(env, args[i], tmp + 1);
		else if (is_valid_key(args[i]) == false)
			error = printf ("export: not an identifier: %s\n", args[i]);
		i++;
	}
	if (error)
		g_last_return = 1;
}
