/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 01:10:24 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/25 19:02:05 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 01:05:11 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/23 01:08:06 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void expander(t_token *token)
{
	int		quote;

	quote = -1;
	while (token)
	{
		if (quote == -1
				&& (token->type == d_quote || token->type == s_quote))
			quote = token->type; 
		else if (token->type == quote)
			quote = -1;
		else if (token->type == word)
		{
			if ((quote == -1 || quote == d_quote) && ft_strchr(token->elem, '$'))
				printf ("%s\n", token->elem);
		}
		token = token->next;
	}
}
