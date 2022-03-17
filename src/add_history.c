/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:59:44 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/17 15:54:46 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_add_history(char *cmd)
{
	static char	*last_cmd;

	if (cmd == NULL || *cmd == '\0')
		return (last_cmd);
	if (last_cmd == NULL
		|| ft_strncmp(last_cmd, cmd, ft_strlen(cmd)))
	{
		free(last_cmd);
		last_cmd = ft_strdup(cmd);
		add_history(cmd);
	}
	return (last_cmd);
}
