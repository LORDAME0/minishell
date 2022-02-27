/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 00:42:53 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/26 19:38:36 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "tokenizer.h"

typedef struct s_pipseq
{
	char	**args;
	int		in_fd;
	int		out_fd;
	struct s_pipseq *next;
} t_pipseq;

void	ft_eval_seq(t_pipseq *seq);
void	parser(t_pipseq **seq, t_token *list);
bool	syntax_analysis(t_token	*tokens);
void	print_seq(t_pipseq *seq);
#endif
