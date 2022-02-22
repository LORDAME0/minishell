/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 23:05:23 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/22 20:35:13 by orahmoun         ###   ########.fr       */
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

t_token	*create_token(char *elem, int type);
char	*return_token_type(int type);
void	print_tokens_types(t_list *tok_list);
void	print_tokens(t_list *tok_list);
void	re_print_command(t_list	*tok_list);
int		and_or_state_token(t_list **head, char *line, int i);
int		redirection_token(t_list **head, char *line, int i);
int		quote_token(t_list **head, char *line, int i);
int		parenthesis_token(t_list **head, char *line, int i);
int		space_token(t_list **head, int i);
bool	is_keyword(char c, char n);
bool	is_quote(char c);
int		add_keyword_token(t_list **head, char *s, int i);
void	add_word_token(t_list **head, char *line, int i);
void	tokenizer(t_list **head, char *line);
#endif
