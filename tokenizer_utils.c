/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/22 20:46:26 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*return_token_type(int type)
{
	if (type == 0)
		return ("d_in");
	else if (type == 1)
		return ("d_out");
	else if (type == 2)
		return ("out");
	else if (type == 3)
		return ("in");
	else if (type == 4)
		return ("word");
	else if (type == 5)
		return ("pip");
	else if (type == 6)
		return ("and_if");
	else if (type == 7)
		return ("or_if");
	else if (type == 8)
		return ("space");
	else if (type == 9)
		return ("d_quote");
	else if (type == 10)
		return ("s_quote");
	else if (type == 11)
		return ("o_parenthesis");
	return ("c_parenthesis");
}

t_token	*create_token(char *elem, int type)
{
	t_token	*token;

	token = malloc (sizeof(token));
	token->elem = elem;
	token->type = type;
	return (token);
}

bool	is_keyword(char c, char n)
{
	if ((c == '(' || c == ')')
		|| (c == '>' || c == '<')
		|| ((c == '&' && n == '&') || c == '|') || c == ' ')
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

int	add_keyword_token(t_list **head, char *s, int i)
{
	if ((s[i] == '(' || s[i] == ')'))
		i = parenthesis_token(head, s, i);
	else if ((s[i] == '>' || s[i] == '<'))
		i = redirection_token(head, s, i);
	else if (((s[i] == '&' && s[i + 1] == '&') || s[i] == '|'))
		i = and_or_state_token(head, s, i);
	else if (s[i] == ' ')
		i = space_token(head, i);
	return (i);
}
