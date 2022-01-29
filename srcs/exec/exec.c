/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:45:12 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/29 16:09:49 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multiple_command_case(t_mini *mini, int command_number)
{
	int		pipe_fd[2048];
	pid_t	pid[1024];
	int		i;
	t_exec	*temp;

	i = 0;
	temp = mini->exec;
	init_pipe_tab(pipe_fd, command_number, pid);
	while (i < command_number)
	{
		if (pipe(&pipe_fd[i * 2]) < 0)
		{
			write(2, "Pipe, memory issue\n", 14);
			ft_free_pipe_tab(pipe_fd, i);
			return ;
		}
		i++;
	}
	i = 0;
	signal(SIGINT, SIG_IGN);
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
			ft_free_pipe_tab(pipe_fd, command_number);
			execute_pipe_command(mini, temp);
		}
		temp = temp->next;
		i++;
	}
	ft_free_pipe_tab(pipe_fd, command_number);
	signal(SIGINT, &sigint_handler_cat);
	signal(SIGQUIT, &sigint_handler_quit);
	ft_wait_fork(pid, command_number);
	return ;
}

void	single_command_case(t_mini *mini)
{
	t_exec	*temp;

	temp = mini->exec;
	if (mini->exec->redir)
		setup_redir(mini, temp);
	if (temp->heredoc_error == 0)
	{
		execute_single_command(mini);
		mini->last_return_value = mini->exec->return_value;
	}
	else
		return ;
	return ;
}

void	ft_execution(t_mini *mini)
{
	int	command_number;

	command_number = ft_lst_size_exec(mini->exec);
	if (command_number == 0)
		return ;
	else if (command_number == 1)
		single_command_case(mini);
	else if (command_number > 1)
		multiple_command_case(mini, command_number);
	free_lst_exec(mini);
	return ;
}
