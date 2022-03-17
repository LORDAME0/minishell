/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 22:55:52 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/17 16:06:51 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	bexit(t_seq *seq, t_env *denv, char *line, char *his)
{
	rl_clear_history();
	free(line);
	free(his);
	free_seq(seq);
	free_env(denv);
	exit(0);
}
