/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:49:06 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/13 22:53:02 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "../libft/libft.h"

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>


/******* GENERAL  UTILS ********/

char		*ft_strjoin_free(char *s1, char *s2);
// int		skip_char(char *str, int *i, char c);
// void		init_indexs(int amount, int value, ...);
// int		skip_until_char(char *str, int *i, char c);
void		panic(bool con, char *msg, const char *func);
bool		is_equal_str(const char *s1, const char *s2);

/******* 2D_ARRAY *******/

char		**init_2d_array(void);
void		free_2d_array(char **array);
size_t	size_of_2d_array(char **array);
int		find_in_2d_array(char **array, char *str);
char		**add_element_2d_array_last(char **array, char *elem);
char		**add_element_2d_array(char **array, char *elem, size_t index);

/******* SHELL UTILS ********/

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env	*next;
}	t_env;

int	g_last_return;

char		*find_value(t_env *env, char *key);
char		**t_env_to_2d_array(t_env *denv);

void		print_logo();
void		free_env(t_env *env);
void		ft_add_history(char *cmd);
void		add_variable_back(t_env **list, t_env *new_var);

t_env		*dup_env(char **env);
t_env		*find_key(t_env *env, char *key);
t_env		*create_variable(char *key, char *value);

/******* TOKENIZER *****/

enum e_token_types {redirection, word, pip, space, d_quote, s_quote, key};

typedef struct s_token
{
	char			*elem;
	int				type;
	struct s_token	*next;
}	t_token;

bool		is_keyword(char c);
bool		is_quote(char c);

char		*return_token_type(int type);
char		*add_keyword_token(t_token **head, char *current, bool open);

void		free_token(t_token *token);
void		free_tokens(t_token *token);
void		add_token_back(t_token **list, t_token *elem);
void		delete_first_token(t_token **list);
// void		print_tokens_types(t_token *tok_list);
// void		print_tokens(t_token *tok_list);
// void		re_print_command(t_token	*tok_list);
void		pip_token(t_token **head);
void		redirection_token(t_token **head, char *line);
void		quote_token(t_token **head, char *current, bool open);
void		space_token(t_token **head);
void		add_word_token(t_token **head, char *start, char *end);
void		add_key_token(t_token **head, char *start, char *end);
void		tokenizer(t_token **head, char *line);

t_token	*create_token(char *elem, int type);
t_token	*get_last_token(t_token *token);

/******* PARSER	*****/

typedef struct s_seq
{
	int				in;
	int				out;
	char				**args;
	struct s_seq	*next;
}	t_seq;

void		free_seq(t_seq *seq);
bool		syntax_analysis(t_token *tokens);

t_seq		*parser(t_token *list);
t_seq		*parsing(char *line, t_env *denv);

t_token	*corrector(t_token *token);
t_token	*expander(t_token *token, t_env *env);

/******* EVAL ********/

#define PID_BUFFER_SIZE 1024

enum	e_builtins {e_echo, e_env, e_export, e_unset, e_cd, e_pwd, e_exit};

int	is_builtin(char *cmd);

void	shell_loop(t_env **denv);
void	eval_seq(t_seq *list, t_env **env);
void	exec_builtin(t_env **env, t_seq *seq, int builtin);

/******* BUILTINS ********/

void	becho(char **args, int fd);
void	bcd(char *path, t_env **env);
void	bexport(char **args, t_env **env, int fd);
void	bunset(char **args, t_env **env);
void  benv(t_env *env, int fd);
void  bpwd(int fd);
void  bexit(t_seq *seq, t_env *denv);

#endif
