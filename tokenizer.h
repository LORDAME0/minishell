/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 23:05:23 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/21 23:29:35 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "main.h"

typedef struct s_token
{
	char	*elem;
	int		type;
}	t_token;

enum e_token_types {d_in, d_out, out, in, word,
	pip, and_if, or_if, space, d_quote, s_quote,
	o_parenthesis, c_parenthesis};

void	print_tokens(t_list *tok_list);
void	re_print_command(t_list	*tok_list);
void	tokenizer(t_list **head, char *line);
#endif
