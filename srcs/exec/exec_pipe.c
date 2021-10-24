/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 23:33:15 by matthieu          #+#    #+#             */
/*   Updated: 2021/10/21 02:56:01 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_pipe_tab(int **pipe_fd, int command_number)
{
	int	i;

	i = 0;
	while (i < command_number)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		pipe_fd = 0;
		i++;
	}
	i = 0;
}

int	init_pipe_tab(int **pipe_fd, int command_number, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < FOPEN_MAX)
		pipe_fd[i++] = 0;
	while (i < command_number)
		pid[i++] = 0;
	return ;
}

void	multiple_command_case(t_mini *mini, int command_number)
{
	int		pipe_fd[FOPEN_MAX][2];
	pid_t	pid[FOPEN_MAX];
	int		i;

	i = 0;
	init_pipe_tab(pipe_fd, command_number, pid);
	while (i < command_number)
	{
		if (pipe(pipe_fd[i]) > 0)
		{
			write(2, "memory issue\n", 14);
			ft_free_pipe_tab(pipe_fd, i);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < command_number)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			write(2, "memory issue\n", 14);
			ft_free_pipe_tab(pipe_fd, command_number);
			return ;
		}
		if (pid[i] == 0)
		{
			if (i == 0)
				dup2(mini->exec->infile_fd, 0);
			else
				dup2(pipe_fd[i - 1][0], 0);
			if (i == command_number - 1)
				dup2(mini->exec->outfile_fd);
			else
				dup2(pipe_fd[1], 1);
		}
		i++;
	}
}
