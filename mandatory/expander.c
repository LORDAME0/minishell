/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:45:31 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/05 18:47:01 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*find_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0
			&& (ft_strlen(key) == ft_strlen(env->key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_token	*split_value(char *value)
{
	int		i;
	char	**sp;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	sp = ft_split(value, ' ');
	if (sp == NULL)
		ft_assert(sp == NULL, "split returned NULL", __func__);
	while (sp[i])
	{
		add_token_back(&tokens, create_token(sp[i], word));
		if (sp[i + 1] != NULL)
			add_token_back(&tokens, create_token(" ", space));
		free(sp[i]);
		i++;
	}
	return (tokens);
}

t_token	*expander(t_token *token, t_env *env)
{
	bool	open;
	t_token	*tmp;
	t_token	*new;

	open = false;
	new = NULL;
	while (token)
	{
		tmp = token->next;
		token->next = NULL;
		if (token->type == d_quote)
			open = !open;
		if (token->type == key)
		{
			if (find_value(env, token->elem))
				add_token_back(&new, split_value(find_value(env, token->elem)));
			else if (open)
				add_token_back(&new, create_token("", word));
			free_token(token);
		}
		else
			add_token_back(&new, token);
		token = tmp;
	}
	return (new);
}
