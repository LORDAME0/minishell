/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:59:44 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/27 20:22:29 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_add_history(char *cmd)
{
	static char	last_cmd[1024];

	if (cmd == NULL || *cmd == '\0')
		return ;
	if (last_cmd[0] == '\0')
	{
		add_history(cmd);
		ft_strlcpy(last_cmd, cmd, ft_strlen(cmd) + 1);
	}
	if (is_equal_str(last_cmd, cmd) == false)
	{
		last_cmd[0] = '\0';
		ft_strlcpy(last_cmd, cmd, ft_strlen(cmd) + 1);
		add_history(cmd);
	}
}
