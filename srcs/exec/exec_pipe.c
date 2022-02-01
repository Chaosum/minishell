/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 23:33:15 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/01 01:19:02 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_pipe_tab(int command_number, int *pipe_fd)
{
	int	i;

	i = 0;
	if (command_number > 1023)
	{
		printf("Too many command number\n");
		ft_free_pipe_tab(pipe_fd, i, 0);
		return (1);
	}
	while (i < command_number)
	{
		if (pipe(&pipe_fd[i * 2]) < 0)
		{
			write(2, "Pipe, memory issue\n", 14);
			return (1);
		}
		i++;
	}
	return (0);
}

void	pipe_execve_fork(t_mini *mini, int *pipe_fd, int i, int command_number)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (i == 0)
		dup2(mini->exec->infile_fd, 0);
	else
		dup2(pipe_fd[(i - 1) * 2], 0);
	if (i == command_number - 1)
		dup2(mini->exec->outfile_fd, 1);
	else
		dup2(pipe_fd[i * 2 + 1], 1);
	ft_free_pipe_tab(pipe_fd, command_number, 0);
}

int	pid_fork_error(pid_t *pid, int i, int *pipe_fd, int command_number)
{
	if (pid[i] < 0)
	{
		ft_free_pipe_tab(pipe_fd, command_number, 0);
		write(2, "memory issue\n", 14);
		return (1);
	}
	return (0);
}

int	execute_pipe_command(t_mini *mini, t_exec *temp)
{
	char	**args;

	args = ft_lstarg_in_tab(temp->arg);
	if (args)
		fork_execve_define_path(mini, args);
	return (1);
}

void	ft_wait_fork(pid_t *pid, int cmd_nbr)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < cmd_nbr)
	{
		waitpid(pid[i], &wstatus, 0);
		i++;
	}
}
