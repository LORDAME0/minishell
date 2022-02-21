/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 22:13:35 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/21 23:40:11 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "tokenizer.h"

t_token	*create_token(char *elem, int type)
{
	t_token	*token;

	token = malloc (sizeof(token));
	token->elem = elem;
	token->type = type;
	return (token);
}

int	and_or_state(t_list **head, char *line, int i)
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

int	redirection_state(t_list **head, char *line, int i)
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


int	quote_state(t_list **head, char *line, int i)
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

int	parenthesis_state(t_list **head, char *line, int i)
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

int	space_state(t_list **head, int i)
{
	ft_lstadd_back(head,
		ft_lstnew(create_token(ft_strdup(" "), space)));
	i++;
	return (i);
}

void	crop(t_list **head, char *line, int i)
{
	char		*tmp;

	tmp = ft_substr(line, 0, i);
	ft_lstadd_back(head,
		ft_lstnew(create_token(tmp, word)));
}

void	tokenizer(t_list **head, char *s)
{
	int		i;
	int		j;
	char	quote;

	quote = -1;
	init_indexs(2, 0, &i, &j);
	i = j = 0;
	while (1337)
	{
		if ((s[i] == '(' || s[i] == ')') && quote == -1)
		{
			if (i != j)
				crop(head, s + j, i - j);
			i = parenthesis_state(head, s, i);
			j = i;
		}
		else if ((s[i] == '>' || s[i] == '<') && quote == -1)
		{
			if (i != j)
				crop(head, s + j, i - j);
			i = redirection_state(head, s, i);
			j = i;
		}
		else if (((s[i] == '&' && s[i + 1] == '&') || s[i] == '|') && quote == -1)
		{
			if (i != j)
				crop(head, s + j, i - j);
			i = and_or_state(head, s, i);
			j = i;
		}
		else if (s[i] == ' ' && quote == -1)
		{
			if (i != j)
				crop(head, s + j, i - j);
			i = space_state(head, i);
			j = i;
		}
		else if ((s[i] == '\'' || s[i] == '\"') && quote == -1)
		{
			if (i != j)
				crop(head, s + j, i - j);
			quote = s[i];
			i = quote_state(head, s, i);
			j = i;
		}
		else if (s[i] == quote)
		{
			if (i != j)
				crop(head, s + j, i - j);
			quote = -1;
			i = quote_state(head, s, i);
			j = i;
		}
		else if (s[i] == 0) 
		{
			if (i != j)
				crop(head, s + j, i - j);
			return ;
		}
		else
			i++;
	}
}
