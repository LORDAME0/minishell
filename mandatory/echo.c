/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:33:42 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/09 16:05:02 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	is_flag(char *str)
{
	BEGIN
	int		i;

	i = 0;
	ft_assert(str == NULL, "NULL PARAM", __func__);
	END
	if(str[0] != '-' || str[1] != 'n')
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
	BEGIN
	int	i;

	i = 0;
	if (fd != -1 && args != NULL && *args != NULL)
	{
		while (args[i] && is_flag(args[i]))
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
	END
}
