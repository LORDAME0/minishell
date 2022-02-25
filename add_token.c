/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:10:38 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/25 18:11:47 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	and_or_state_token(t_token **head, char *line, int i)
{
	if (line[i] == line[i + 1])
	{
		if (line[i] == '&')
			add_token_back(head,
				create_token(ft_strdup("&&"), and_if));
		else
			add_token_back(head,
				create_token(ft_strdup("||"), or_if));
		i += 2;
	}
	else if (line[i] == '|')
	{
		add_token_back(head, create_token(ft_strdup("|"), pip));
		i++;
	}
	return (i);
}

int	redirection_token(t_token **head, char *line, int i)
{
	if (line[i] == line[i + 1])
	{
		if (line[i] == '>')
			add_token_back(head,
				create_token(ft_strdup(">>"), redirection));
		else
			add_token_back(head,
				create_token(ft_strdup("<<"), redirection));
		i += 2;
	}
	else
	{
		if (line[i] == '>')
			add_token_back(head,
				create_token(ft_strdup(">"), redirection));
		else
			add_token_back(head,
				create_token(ft_strdup("<"), redirection));
		i++;
	}
	return (i);
}

int	quote_token(t_token **head, char *line, int i)
{
	if (line[i] == '\"')
		add_token_back(head,
			create_token(ft_strdup("\""), d_quote));
	else
		add_token_back(head,
			create_token(ft_strdup("\'"), s_quote));
	i++;
	return (i);
}

int	parenthesis_token(t_token **head, char *line, int i)
{
	if (line[i] == '(')
		add_token_back(head,
			create_token(ft_strdup("("), o_parenthesis));
	else
		add_token_back(head,
			create_token(ft_strdup(")"), c_parenthesis));
	i++;
	return (i);
}

int	space_token(t_token **head, int i)
{
	t_token	*last_token;

	if (*head)
	{
		last_token = get_last_token(*head);
		if (head && last_token->type != space)
			add_token_back(head,
				create_token(ft_strdup(" "), space));
	}
	i++;
	return (i);
}
