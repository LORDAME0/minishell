/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:10:38 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/05 06:34:27 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	add_word_token(t_token **head, char *start, char *end)
{
	char		*tmp;

	if (start != end)
	{
		tmp = ft_substr(start, 0, end - start);
		add_token_back(head,
			create_token(tmp, word));
		free(tmp);
	}
}

void	add_key_token(t_token **head, char *start, char *end)
{
	char		*tmp;

	if (start != end)
	{
		tmp = ft_substr(start, 0, end - start);
		add_token_back(head,
			create_token(tmp, key));
		free(tmp);
	}
}
