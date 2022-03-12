/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 01:42:37 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/11 21:01:15 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


t_token	*joiner(t_token *token)
{
	t_token	*new;
	t_token	*tmp;
	char	*str;

	new = NULL;
	panic(token == NULL, "NULL PARAM", __func__);
	while (token)
	{
		tmp = token->next;
		if (token->type == word)
		{
			str = ft_strdup("");
			while (token && token->type == word)
			{
				tmp = token->next;
				str = ft_strjoin_free(str, token->elem);
				free(token->elem);
				free(token);
				token = tmp;
			}
			add_token_back(&new, create_token(str, word));
			free (str);
		}
		if (token && token->type != space)
		{
			tmp = token->next;
			token->next = NULL;
			add_token_back(&new, token);
		}
    // else if (token && token->type == space)
    // {
      // free(token->elem);
      // free(token);
      // token = NULL;
    // }
		token = tmp;
	}
	return (new);
}

t_token	*remove_space(t_token *token)
{
  // printf("$$$$$$$$$$$$$$$$ HERE $$$$$$$$$$\n");
  // print_tokens(token);
  // printf("$$$$$$$$$$$$$$$$ HERE $$$$$$$$$$\n");
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	panic(token == NULL, "NULL PARAM", __func__);
	while (token)
	{
		tmp = token->next;
		token->next = NULL;
		if (token && token->type != space)
			add_token_back(&new, token);
		else if (token && token->type == space)
		{
      // printf("$$$$$$$$$$$$$$$$ LEAKS $$$$$$$$$$\n");
			free(token->elem);
			free(token);
			token = NULL;
		}
		token = tmp;
	}
  // system("leaks minishell");
	return (new);
}

t_token	*remove_quotes(t_token *token)
{
	t_token	*new;
	t_token	*tmp;

  // printf("$$$$$$$$$$$$$$$$ START TOKEN $$$$$$$$$$\n");
  // print_tokens(token);
  // printf("$$$$$$$$$$$$$$$$ START TOKEN $$$$$$$$$$\n");
	new = NULL;
	panic(token == NULL, "NULL PARAM", __func__);
	while (token)
	{
		tmp = token->next;
		token->next = NULL;
		if (token->type != s_quote
			&& token->type != d_quote)
			add_token_back(&new, token);
		else
		{
			free(token->elem);
			free(token);
			token = NULL;
		}
		token = tmp;
	}
  // printf("$$$$$$$$$$$$$$$$ END TOKEN $$$$$$$$$$\n");
  // print_tokens(token);
  // printf("$$$$$$$$$$$$$$$$ END TOKEN $$$$$$$$$$\n");
	return (new);
}

t_token	*corrector(t_token *token)
{
	panic(token == NULL, "NULL PARAM", __func__);
	token = remove_quotes(token);
	token = joiner(token);
  token = remove_space(token);
	return (token);
}
