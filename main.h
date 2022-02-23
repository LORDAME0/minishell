/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:49:06 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/23 01:31:36 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "tokenizer.h"
# include "parser.h"
typedef struct s_info
{
	t_list	*env;
}	t_info;

t_info	g_info;
typedef struct s_section
{
	char	*command;
	char 	**args;
	char 	*infile;
	char 	*outfile;
}				t_section;
/******* UTILS ********/

int		skip_char(char *str, int *i, char c);
int		skip_until_char(char *str, int *i, char c);
void	init_indexs(int amount, int value, ...);

/******* PARSING TOOLS *****/


/******* BUILTINS ********/

#endif
