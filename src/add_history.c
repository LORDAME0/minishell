/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:59:44 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/08 23:03:32 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_add_history(char *cmd)
{
	static char	*last_cmd;

	if (cmd == NULL || *cmd == '\0')
		return ;
	if (last_cmd == NULL
		|| ft_strncmp(last_cmd, cmd, ft_strlen(cmd)))
	{
		last_cmd = cmd;
		add_history(cmd);
	}
}
