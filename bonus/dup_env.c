/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 01:28:05 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/23 01:31:39 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	dup_env(char **env)
{
	t_list	*head;
	size_t	i;

	i = 0;
	head = NULL;
	if (env == NULL)
	{
		printf ("MiniSHELL :: env error\n");
		exit (1);
	}
	while (env[i])
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(env[i])));
		i++;
	}
	g_info.env = head;
}
