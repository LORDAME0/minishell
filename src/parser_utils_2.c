/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:49:47 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/16 19:13:56 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	heredoc(char *delimiter)
{
	char	*total;
	char	*line;
	int		fd[2];

	pipe (fd);
	total = ft_strdup("");
	while (1)
	{
		line = readline("heredoc> ");
		if ((ft_strncmp(line, delimiter, ft_strlen (delimiter)) == 0
				&& ft_strlen(delimiter) == ft_strlen(line)))
			break ;
		total = ft_strjoin_free(total, line);
		total = ft_strjoin_free(total, "\n");
		free(line);
	}
	write (fd[1], total, ft_strlen(total));
	free(total);
	close (fd[1]);
	return (fd[0]);
}

void	eval_io(t_seq *seq, char *rederiction_type, char *file)
{
	panic(rederiction_type == NULL || file == NULL, "NULL PARAM", __func__);
	if (rederiction_type[0] == '<')
	{
		safe_close(seq->in);
		if (rederiction_type[1])
			seq->in = heredoc(file);
		else
			seq->in = open (file, O_RDONLY);
		if (seq->in == -1)
			perror("Error :");
	}
	else
	{
		safe_close(seq->out);
		if (rederiction_type[1])
			seq->out = open (file, O_APPEND | O_WRONLY | O_CREAT, 0777);
		else
			seq->out = open (file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (seq->out == -1)
			perror("Error :");
	}
}

t_token	*eval_redirection(t_seq *seq, t_token *token)
{
	char	*rederiction_type;

	rederiction_type = token->elem;
	token = token->next;
	eval_io(seq, rederiction_type, token->elem);
	if (seq->in < 0 || seq->out < 0)
	{
		while (token && token->type != pip)
			token = token->next;
		free_2d_array(seq->args);
		seq->args = NULL;
	}
	return (token);
}

void	eval_pipes(t_seq *seq)
{
	bool		first;
	bool		last;
	int			fd[2];

	first = true;
	last = false;
	if (seq == NULL || seq->next == NULL)
		return ;
	while (seq)
	{
		if (first == false)
			seq->in = fd[0];
		if (last == false)
		{
			pipe(fd);
			seq->out = fd[1];
			first = false;
		}
		seq = seq->next;
		last = (seq && seq->next == NULL);
	}
}
