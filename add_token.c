/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:10:38 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/22 20:40:47 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	and_or_state_token(t_list **head, char *line, int i)
{
	if (line[i] == line[i + 1])
	{
		if (line[i] == '&')
			ft_lstadd_back(head,
				ft_lstnew(create_token(ft_strdup("&&"), and_if)));
		else
			ft_lstadd_back(head,
				ft_lstnew(create_token(ft_strdup("||"), or_if)));
		i += 2;
	}
	else if (line[i] == '|')
	{
		ft_lstadd_back(head, ft_lstnew(create_token(ft_strdup("|"), pip)));
		i++;
	}
	return (i);
}

int	redirection_token(t_list **head, char *line, int i)
{
	if (line[i] == line[i + 1])
	{
		if (line[i] == '>')
			ft_lstadd_back(head,
				ft_lstnew(create_token(ft_strdup(">>"), d_out)));
		else
			ft_lstadd_back(head,
				ft_lstnew(create_token(ft_strdup("<<"), d_in)));
		i += 2;
	}
	else
	{
		if (line[i] == '>')
			ft_lstadd_back(head,
				ft_lstnew(create_token(ft_strdup(">"), out)));
		else
			ft_lstadd_back(head,
				ft_lstnew(create_token(ft_strdup("<"), in)));
		i++;
	}
	return (i);
}

int	quote_token(t_list **head, char *line, int i)
{
	if (line[i] == '\"')
		ft_lstadd_back(head,
			ft_lstnew(create_token(ft_strdup("\""), d_quote)));
	else
		ft_lstadd_back(head,
			ft_lstnew(create_token(ft_strdup("\'"), s_quote)));
	i++;
	return (i);
}

int	parenthesis_token(t_list **head, char *line, int i)
{
	if (line[i] == '(')
		ft_lstadd_back(head,
			ft_lstnew(create_token(ft_strdup("("), o_parenthesis)));
	else
		ft_lstadd_back(head,
			ft_lstnew(create_token(ft_strdup(")"), c_parenthesis)));
	i++;
	return (i);
}

int	space_token(t_list **head, int i)
{
	t_token	*last_token;

	if (*head)
	{
		last_token = (t_token *)ft_lstlast(*head)->content;
		if (head && last_token->type != space)
			ft_lstadd_back(head,
				ft_lstnew(create_token(ft_strdup(" "), space)));
	}
	i++;
	return (i);
}
