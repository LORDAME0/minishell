/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:22:16 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/12 18:14:04 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_seq	*parsing(char *line, t_env *denv)
{
	t_token	*list;
	t_seq	*seq;

	list = NULL;
	seq = NULL;
	if (line)
		tokenizer(&list, line);
	if (list && syntax_analysis(list) == false)
	{
		list = expander(list, denv);
		if (list)
			list = corrector(list);
		if (list)
			seq = parser(list);
	}
	free_tokens(list);
	return (seq);
}
