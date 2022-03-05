/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:21:35 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/05 06:37:41 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char *find_in_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0
			&& (ft_strlen(key) == ft_strlen(env->key)))
				return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

t_token	*split_into_word_tokens(char *value)
{
	int 	i;
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
	char	*value;
	t_token	*tmp;
	t_token	*new_list;

	new_list = NULL;
	while (token)
	{
		tmp = token->next;
		token->next = NULL;
		if (token->type == key)
		{
			value = find_in_env(env, token->elem);
			free (token->elem);
			free (token);
			if (value)
				add_token_back(&new_list, split_into_word_tokens(value));
			free(value);
		}
		else
			add_token_back(&new_list, token);
		token = tmp;
	}
	return (new_list);
}
