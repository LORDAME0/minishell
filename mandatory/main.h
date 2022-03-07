/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:49:06 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/07 14:23:35 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/* typedef struct s_info */
/* { */
/* 	t_list	*env; */
/* }	t_info; */

/* t_info	g_info; */
/* typedef struct s_section */
/* { */
/* 	char	*command; */
/* 	char 	**args; */
/* 	char 	*infile; */
/* 	char 	*outfile; */
/* }				t_section; */
/******* UTILS ********/

int		skip_char(char *str, int *i, char c);
int		skip_until_char(char *str, int *i, char c);
void	ft_assert(bool con, char *msg, const char *func);
void	init_indexs(int amount, int value, ...);

/******* 2D_ARRAY *******/

void	print_2d_array(char **array, int fd);
size_t	size_of_2d_array(char **array);
char	**dup_2d_array(char **array);
char	**delete_element_2d_array(char **array, size_t index);
int		find_in_2d_array(char **array, char *str);
char	**init_2d_array(void);
void	free_2d_array(char **array);
char	**add_element_2d_array(char **array, char *elem, size_t index);
char	**join_2d_array(char **dst, char **source);
char	**add_element_2d_array_last(char **array, char *elem);
char	*join_2d_array_into_str(char **array);
char	**split_and_join(char **array, char *line, char c);

/******* SHELL UTILS ********/

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	free_env(t_env *env);
t_env	*dup_env(char **env);

/******* TOKENIZER *****/

enum e_token_types {redirection, word, pip, space, d_quote, s_quote, key};

typedef struct s_token
{
	char			*elem;
	int				type;
	struct s_token	*next;
}	t_token;

void	free_token(t_token *token);
void	free_tokens(t_token *token);
t_token	*create_token(char *elem, int type);
t_token	*get_last_token(t_token *token);
void	add_token_back(t_token **list, t_token *elem);
void	delete_first_token(t_token **list);
char	*return_token_type(int type);
void	print_tokens_types(t_token *tok_list);
void	print_tokens(t_token *tok_list);
void	re_print_command(t_token	*tok_list);
void	pip_token(t_token **head);
void	redirection_token(t_token **head, char *line);
void	quote_token(t_token **head, char *current, bool open);
void	space_token(t_token **head);
bool	is_keyword(char c);
bool	is_quote(char c);
char	*add_keyword_token(t_token **head, char *current, bool open);
void	add_word_token(t_token **head, char *start, char *end);
void	add_key_token(t_token **head, char *start, char *end);
void	tokenizer(t_token **head, char *line);

/******* PARSER	*****/

typedef struct s_seq
{
	char			**args;
	int				in;
	int				out;
	struct s_seq	*next;
}	t_seq;

void	free_seq(t_seq *seq);
t_token	*corrector(t_token *token);
t_token	*expander(t_token *token, t_env *env);
bool	syntax_analysis(t_token *tokens);
t_seq	*parser(t_token *list);

// EVAL
void	eval_seq(t_seq *list, char **env);

/******* BUILTINS ********/

#endif
