/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:45:31 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/12 10:59:35 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*find_value(t_env *env, char *key)
{
	if (*key == '?')
		return (ft_itoa(g_global.last_return));
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
		panic(sp == NULL, "split returned NULL", __func__);
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

void	expand_key(t_token **token, t_token *key, t_env *env)
{
	char	*value;

	value = find_value(env, key->elem);
	if (get_last_token(*token)->type != d_quote)
		add_token_back(token,
			split_value(value));
	else
		add_token_back(token,
			create_token(value, word));
}

t_token	*expander(t_token *token, t_env *env)
{
	bool		open;
	t_token	*tmp;
	t_token	*new;

	new = NULL;
	open = false;
	while (token)
	{
		tmp = token->next;
		token->next = NULL;
		if (token->type == d_quote)
			open = !open;
		if (token->type == key)
		{
			if (find_value(env, token->elem))
				expand_key(&new, token, env);
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
