/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 23:05:23 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/25 19:11:36 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TOKENIZER_H
# define TOKENIZER_H
#include "libft/libft.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct s_token
{
	char	*elem;
	int		type;
	struct s_token	*next;
}	t_token;

enum e_token_types {redirection, word, pip, and_if,
	or_if, space, d_quote, s_quote,
	o_parenthesis, c_parenthesis};

t_token	*create_token(char *elem, int type);
t_token	*get_last_token(t_token *token);
void	add_token_back(t_token **list, t_token *elem);
char	*return_token_type(int type);
void	print_tokens_types(t_token *tok_list);
void	print_tokens(t_token *tok_list);
void	re_print_command(t_token	*tok_list);
int		and_or_state_token(t_token **head, char *line, int i);
int		redirection_token(t_token **head, char *line, int i);
int		quote_token(t_token **head, char *line, int i);
int		parenthesis_token(t_token **head, char *line, int i);
int		space_token(t_token **head, int i);
bool	is_keyword(char c, char n);
bool	is_quote(char c);
int		add_keyword_token(t_token **head, char *s, int i);
void	add_word_token(t_token **head, char *line, int i);
void	tokenizer(t_token **head, char *line);
#endif
