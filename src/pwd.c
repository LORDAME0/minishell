/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaamaou <rnaamaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:58:28 by rnaamaou          #+#    #+#             */
/*   Updated: 2022/06/27 16:58:30 by rnaamaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "main.h"

void	bpwd(int fd)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, fd);
	ft_putstr_fd("\n", fd);
}
