/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:33:42 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/08 22:48:47 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	is_flag(char *str)
{
	int		i;

	i = 0;
	if(str[0] != '-')
		return (0);
	++i;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	echo(char **args, int fd)
{
	int	i;

	i = 0;
	if (args != NULL && *args != NULL)
	{
		while (is_flag(args[i]))
			++i;
		while (args[i])
		{
			ft_putstr_fd(args[i], fd);
			if (args[i + 1])
				ft_putstr_fd(" ", fd);
			i++;
		}
		if (is_flag(args[0]) != true)
			ft_putstr_fd("\n", fd);
	}
	else
		ft_putstr_fd("\n", fd);
}
