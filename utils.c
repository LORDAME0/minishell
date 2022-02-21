/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:01:57 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/21 17:02:52 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdarg.h>

int	skip_char(char *str, int *i, char c)
{
	while (str[*i] && str[*i] == c)
		(*i)++;
	if (str[*i] == '\0')
		return (-1);
	return (*i);
}

int	skip_until_char(char *str, int *i, char c)
{
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (str[*i] == '\0')
		return (-1);
	return (*i);
}

void	init_indexs(int amount, int value, ...)
{
	va_list	args;
	int		*tmp;

	va_start(args, value);
	while (amount--)
	{
		tmp = va_arg(args, int *);
		*tmp = value;
	}
	va_end(args);
}
