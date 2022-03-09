/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/09 15:52:48 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


const char *str = ".##.....##.####.##....##.####..######..##.....##.########.##.......##......";
const char *str1 = ".###...###..##..###...##..##..##....##.##.....##.##.......##.......##......";
const char *str2 = ".####.####..##..####..##..##..##.......##.....##.##.......##.......##......";
const char *str3 = ".##.###.##..##..##.##.##..##...######..#########.######...##.......##......";
const char *str4 = ".##.....##..##..##..####..##........##.##.....##.##.......##.......##......";
const char *str5 = ".##.....##..##..##...###..##..##....##.##.....##.##.......##.......##......";
const char *str6 = ".##.....##.####.##....##.####..######..##.....##.########.########.########";

void	handler(int sig)
{
}
                     

int	main(int n, char **args, char **env)
{
	t_token		*list;
	t_env		*denv;
	t_seq		*seq;
	char		*line;

	(void)n;
	(void)args;
	denv = dup_env(env); 
	g_global.last_return = 0;
	printf ("%s\n", str);
	printf ("%s\n", str1);
	printf ("%s\n", str2);
	printf ("%s\n", str3);
	printf ("%s\n", str4);
	printf ("%s\n", str5);
	printf ("%s\n", str6);
	signal(SIGINT, handler);
	seq = NULL;
	line = NULL;
	list = NULL;
	while (1337)
	{
		line = readline("$> ");
		if (line == NULL)
			exit (0);
		if (*line == '\0')
			continue ;
		if (ft_strncmp("exit", line, ft_strlen(line)) == 0)
			exit (0);
		ft_add_history(line);
		tokenizer(&list, line);
		if (list && syntax_analysis(list) == false)
		{
			list = expander(list, denv);
			if (list)
				list = corrector(list);
			if (list)
			{
				seq = parser(list);
				if (seq == NULL)
				{
					list = NULL;
					line = NULL;
					continue ;
				}
				eval_seq(seq, env);
				free_seq(seq);
			}
			list = NULL;
			seq = NULL;
			line = NULL;
		}
		else
		{
			list = NULL;
			line = NULL;
		}
	}
		/* free_tokens(list2); */
		/* free_env(denv); */
		/* system("leaks minishell"); */
}
