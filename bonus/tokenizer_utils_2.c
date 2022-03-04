/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:58:08 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/26 17:15:50 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*create_token(char *elem, int type)
{
	t_token	*token;

	token = malloc (sizeof(t_token));
	token->elem = ft_strdup(elem);
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*get_last_token(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	add_token_back(t_token **list, t_token *new_token)
{
	if (*list == NULL)
		*list = new_token;
	else
		(get_last_token(*list))->next = new_token;
}
