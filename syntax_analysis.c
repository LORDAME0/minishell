/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 00:32:48 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/22 20:43:00 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/* void	free_elem(void *content) */
/* { */
/*  	t_token	*token; */

/* 	token = (t_token *)content; */
/* 	free(token->elem); */
/* 	free(content); */
/* } */

/* void	remove_redondant_space(t_list **head) */
/* { */
/*  	t_token	*current_token; */
/*  	t_token	*previous_token; */
/*  	t_token	*next_token; */
/* 	t_list	*previous_head; */

/* 	current_token = NULL; */
/* 	next_token = NULL; */
/* 	previous_head = NULL; */
/* 	while (head) */
/* 	{ */
/*  		previous_token = current_token; */
/* 		current_token = (t_token *)(*head)->content; */
/* 		if ((*head)->next) */
/* 			next_token = (t_token *)(*head)->next->content; */
/* 		printf ("test\n"); */
/* 		if (next_token && previous_token && head */
/* 			&& current_token->type == space */
/* 			&& next_token->type != word */
/* 			&& previous_token->type != word) */
/* 		{ */
/* 			previous_head->next = (*head)->next; */
/* 			ft_lstdelone(*head, free_elem); */
/* 			(*head) = (*head)->next; */
/* 		} */
/* 		else */
/* 		{ */
/* 			previous_head = *head; */
/* 			(*head) = (*head)->next; */
/* 		} */
/* 	} */
/* } */

bool	syntax_analysis(t_list *tokens)
{
	bool		open_quotes;
	t_token		*current_token;
	int			matching_paren;

	current_token = NULL;
	open_quotes = false;
	matching_paren = 0;
	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		if (current_token->type == d_quote || current_token->type == s_quote)
			open_quotes = !open_quotes;
		if (current_token->type == o_parenthesis)
			matching_paren++;
		if (current_token->type == c_parenthesis)
			matching_paren--;
		tokens = tokens->next;
	}
	if (matching_paren || open_quotes)
		return (true);
	return (false);
}

/* bool	syntax_analysis_p_a_o(t_list *tokens) */
/* { */

/* } */

/* bool	syntax_analysis(t_list *tokens) */
/* { */
/* 	return (false); */
/* } */
