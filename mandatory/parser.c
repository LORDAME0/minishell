#include "parser.h"
#include <fcntl.h>
#include "2d_array.h"
#include "main.h"

t_pipseq	*create_seq(char **args, int in, int out)
{
	t_pipseq	*pip;

	pip = malloc (sizeof(t_pipseq));
	pip->args = args;
	pip->in_fd = in;
	pip->out_fd = out;
	pip->next = NULL;
	return (pip);
}

t_pipseq	*get_last_pip(t_pipseq *pip)
{
	if (pip == NULL)
		return (NULL);
	while (pip->next != NULL)
		pip = pip->next;
	return (pip);
}

void	add_pip_back(t_pipseq **list, t_pipseq *new_pip)
{
	if (*list == NULL)
		*list = new_pip;
	else
		(get_last_pip(*list))->next = new_pip;
}

int	eval_redirections(char *elem, char *io_file)
{
	int fd;
	if (elem[0] == '>')
	{
		fd = open (io_file, O_WRONLY | O_CREAT | 0777);
		if (fd == - 1)
			perror ("Error");
		return (fd);
	}
	return (-1);
}

void	parser(t_pipseq **seq, t_token *list)
{
	int		i;
	int		j;
	int		out_fd;
	int		in_fd;
	char	*red;
	char	**args;
	int		fd[1024][2];

	i = 0;
	j = 0;
	args = NULL;
	in_fd = 0;
	out_fd = 1;
	red = NULL;
	while (list)
	{
		while (list && list->type != pip)
		{
			if (args == NULL)
				args = init_2d_array();
			args = add_element_2d_array_last(args, list->elem);
			list = list->next;
		}
		if (list && list->type == pip)
		{
			pipe(fd[j]);
			out_fd = fd[j][1];
			list = list->next;
		}
		else
			out_fd = 1;
		if (*seq != NULL)
		{
			in_fd = fd[j][0];
			j++;
		}
		else
			in_fd = 0;
		add_pip_back(seq, create_seq(args, in_fd, out_fd));
	}
}

void	print_seq(t_pipseq *seq)
{
	int i;

	i = 0;
	while (seq)
	{
		while (seq->args[i])
		{
			printf ("args :: %s\n", seq->args[i]);
			i++;
		}
		printf ("in ::  %d\n", seq->in_fd);
		printf ("out ::  %d\n", seq->out_fd);
		seq = seq->next;
	}
}

void	ft_exec(t_pipseq seq)
{
	int state;

	printf ("%s begin for command %s\n", __func__, seq.args[0]);
	pid_t pid = fork();
	if (pid == 0)
	{
		if (seq.in_fd != 0)
			dup2(seq.in_fd, 0);
		if (seq.out_fd != 1)
			dup2(seq.out_fd, 1);
		execve(seq.args[0], seq.args, ENV);
	}
	if (pid != 0)
	{
		wait(&state);
		printf ("%s end for command %s\n", __func__, seq.args[0]);
	}
}

void	ft_eval_seq(t_pipseq *seq)
{
	printf ("%s begin\n", __func__);
	while (seq)
	{
		ft_exec(*seq);
		seq = seq->next;
	}
	printf ("%s end\n", __func__);
}
