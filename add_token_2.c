/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:40:55 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/25 19:42:57 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	add_word_token(t_token **head, char *start, char *end)
{
	char		*tmp;

	if (start != end)
	{
		tmp = ft_substr(start, 0, end - start);
		add_token_back(head,
			create_token(tmp, word));
	}
}
