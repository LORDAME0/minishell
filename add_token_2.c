/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:40:55 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/22 23:28:25 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	add_word_token(t_list **head, char *line, int i)
{
	char		*tmp;

	if (i != 0)
	{
		tmp = ft_substr(line, 0, i);
		ft_lstadd_back(head,
			ft_lstnew(create_token(tmp, word)));
	}
}
