/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:01:57 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/13 08:52:06 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdarg.h>

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

void	panic(bool con, char *msg, const char *func)
{
	if (con == true)
	{
		printf ("Panic attack [%s] : %s\n", msg, func);
		exit (1);
	}
}

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

bool	is_equal_str(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (false);
	return (ft_strncmp(s1, s2, s1_len) == 0);
}
