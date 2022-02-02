/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:45:12 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/02 04:26:01 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multiple_command_case(t_mini *mini, int command_number, int i)
{
	int		pipe_fd[2048];
	pid_t	pid[1024];
	t_exec	*temp;

	temp = mini->exec;
	if (init_pipe_tab(pipe_fd, command_number, pid))
		return ;
	while (i < command_number)
	{
		pid[i] = fork();
		if (pid_fork_error(pid, i, pipe_fd, command_number))
			return ;
		if (pid[i] == 0)
		{
			if (temp->redir)
				setup_redir(mini, temp);
			pipe_execve_fork(temp, pipe_fd, i, command_number);
			execute_pipe_command(mini, temp);
		}
		temp = temp->next;
		i++;
	}
	ft_free_pipe_tab(pipe_fd, command_number, 0);
	ft_wait_fork(pid, command_number);
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
	{
		signal(SIGINT, SIG_IGN);
		multiple_command_case(mini, command_number, 0);
	}
	free_lst_exec(mini);
	return ;
}
