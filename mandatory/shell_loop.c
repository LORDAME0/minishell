/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:37:11 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/09 22:53:53 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	shell_loop(t_env *denv)
{
	BEGIN
	t_seq	*seq;
	char	*line;

	while (1337)
	{
		line = readline("$> ");
		if (line == NULL)
			exit (0);
		if (*line == '\0')
			continue ;
		if (ft_strncmp("exit", line, ft_strlen(line)) == 0)
		{
			free (line);
			return ;
		}
		ft_add_history(line);
		seq = parsing(line, denv);
		eval_seq(seq, denv);
		free(line);
		free_seq(seq);
		seq = NULL;
		line = NULL;
	}
	END
}
