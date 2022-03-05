/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:10:38 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/05 05:48:17 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	pip_token(t_token **head)
{
	add_token_back(head, create_token("|", pip));
}

void	redirection_token(t_token **head, char *current)
{
	if (*current == *(current + 1))
	{
		if (*current == '>')
			add_token_back(head,
				create_token(">>", redirection));
		else
			add_token_back(head,
				create_token("<<", redirection));
	}
	else
	{
		if (*current == '>')
			add_token_back(head,
				create_token(">", redirection));
		else
			add_token_back(head,
				create_token("<", redirection));
	}
}

void	quote_token(t_token **head, char *current)
{
	if (*head)
	{
		if (get_last_token(*head)->elem[0] == *current)
			add_token_back(head,
				create_token("", word));
	}
	if (*current == '\"')
		add_token_back(head,
			create_token("\"", d_quote));
	else if (*current == '\'')
		add_token_back(head,
			create_token("\'", s_quote));
}

void	space_token(t_token **head)
{
	t_token	*last_token;

	if (*head)
	{
		last_token = get_last_token(*head);
		if (head && last_token->type != space)
			add_token_back(head,
				create_token(" ", space));
	}
}
