/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 23:33:15 by matthieu          #+#    #+#             */
/*   Updated: 2021/10/27 03:00:39 by mservage         ###   ########.fr       */
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

int	execute_pipe_command(t_mini *mini, t_exec *temp)
{
	char	**args;

	args = ft_lstarg_in_tab(temp->arg);
	fork_execve_define_path(mini, temp, args);
}

void	ft_wait_fork(t_mini *mini, t_exec *temp, pid_t *pid, int cmd_nbr)
{
	int	i;

	i = 0;
	while (i < cmd_nbr)
	{
		wait(pid[i]);
		i++;
	}
}

void	multiple_command_case(t_mini *mini, int command_number)
{
	int		pipe_fd[FOPEN_MAX][2];
	pid_t	pid[FOPEN_MAX];
	int		i;
	t_exec	*temp;

	i = 0;
	temp = mini->exec;
	init_pipe_tab(pipe_fd, command_number, pid);
	while (i < command_number)
	{
		if (pipe(pipe_fd[i]) > 0)
		{
			write(2, "Pipe, memory issue\n", 14);
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
				dup2(mini->exec->outfile_fd, 1);
			else
				dup2(pipe_fd[i][1], 1);
			ft_free_pipe_tab(pipe_fd, command_number);
			execute_pipe_command(mini, temp);
		}
		temp = temp->next;
		i++;
	}
	ft_free_pipe_tab(pipe_fd, command_number);
	ft_wait_fork(mini, temp, pid, command_number);
	return ;
}
