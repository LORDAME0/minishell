/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 01:28:05 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/05 06:22:30 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

t_env	*create_variable(char *key, char *value)
{
	t_env	*variable;

	variable = malloc (sizeof(t_env));
	variable->key = key;
	variable->value = value;
	variable->next = NULL;
	return (variable);
}

t_env	*get_last_var(t_env *var)
{
	if (var == NULL)
		return (NULL);
	while (var->next != NULL)
		var = var->next;
	return (var);
}

void	add_variable_back(t_env **list, t_env *new_var)
{
	if (*list == NULL)
		*list = new_var;
	else
		(get_last_var(*list))->next = new_var;
}

t_env	*dup_env(char **env)
{
	size_t	i;
	t_env	*head;
	char	*key;
	char	*value;

	i = 0;
	head = NULL;
	ft_assert(env == NULL, "NULL pointer as param", __func__);
	while (env[i])
	{
		key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		if (ft_strncmp(key, "OLDPWD", ft_strlen(key)) == 0)
			value = ft_strdup("");
		else if (ft_strncmp(key, "SHLVL", ft_strlen(key)) == 0)
			value = ft_itoa(ft_atoi(ft_strchr(env[i], '=') + 1) + 1);
		else
			value = ft_strdup(ft_strchr(env[i], '=') + 1);
		add_variable_back(&head, create_variable(key, value));
		i++;
	}
	return (head);
}

/* int main(int n, char **args, char **env) */
/* { */
/* 	t_env *head = dup_env(env); */

/* 	while (head) */
/* 	{ */
/* 		printf ("%s=%s\n", head->key, head->value); */
/* 		head = head->next; */
/* 	} */
/* } */
