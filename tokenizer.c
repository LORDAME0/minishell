/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 22:13:35 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/23 00:31:07 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "tokenizer.h"

void	tokenizer(t_list **head, char *s)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = -1;
	init_indexs(2, 0, &i, &j);
	while (s[i])
	{
		if (is_keyword(s[i], s[i + 1]) && quote == -1)
		{
			add_word_token(head, s + j, i - j);
			i = add_keyword_token(head, s, i);
			j = i;
		}
		else if (is_quote(s[i]) && (quote == -1 || s[i] == quote))
		{
			add_word_token(head, s + j, i - j);
			if (quote == -1)
				quote = s[i];
			else
				quote = -1;
			i = quote_token(head, s, i);
			j = i;
		}
		else if (s[i + 1] == 0)
			add_word_token(head, s + j, ++i - j);
		else
			i++;
	}
}
