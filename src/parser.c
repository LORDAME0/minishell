/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:39:59 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/16 19:22:29 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_seq	*pre_parser(t_token *list)
{
	t_seq	*tmp;
	t_seq	*head;

	head = NULL;
	while (list)
	{
		tmp = create_seq(init_2d_array(), 0, 1);
		tmp->args[0] = NULL;
		while (list && list->type != pip)
			list = list->next;
		add_seq_back(&head, tmp);
		if (list && list->type == pip)
			list = list->next;
	}
	eval_pipes(head);
	return (head);
}

t_seq	*parser(t_token *list)
{
	t_seq	*head;
	t_seq	*tmp;

	head = pre_parser(list);
	tmp = head;
	while (list)
	{
		while (list && list->type != pip)
		{
			if (list->type == redirection)
				list = eval_redirection(tmp, list);
			else
				tmp->args = add_element_2d_array_last(tmp->args,
						ft_strdup(list->elem));
			if (list && list->type != pip)
				list = list->next;
		}
		if (list && list->type == pip)
		{
			tmp = tmp->next;
			list = list->next;
		}
	}
	return (head);
}
// #ifdef DEBUG
	// print_seq(head);
// #endif
// void	print_seq(t_seq *seq)
// {
	// int	i;
//
	// i = 1;
	// if (seq == NULL)
		// return ;
	// while (seq)
	// {
		// if (seq->args)
		// {
			// printf ("CMD :: %s\n", seq->args[0]);
			// if (seq->args[0] && seq->args[1])
			// {
				// while (seq->args[i])
				// {
					// printf ("ARG[%d] :: %s\n", i, seq->args[i]);
					// i++;
				// }
				// i = 0;
			// }
		// }
		// else
			// printf ("CMD :: %s\n", NULL);
		// printf ("IN :: %d\n", seq->in);
		// printf ("OUT :: %d\n", seq->out);
		// seq = seq->next;
	// }
// }
//
