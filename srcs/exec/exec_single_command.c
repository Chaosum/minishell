/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:29:08 by mservage          #+#    #+#             */
/*   Updated: 2021/12/08 01:54:24 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_single_case_function(t_mini *mini, t_exec *temp)
{
	int		fd[2];
	pid_t	pid;
	char	**args;

	if (pipe(fd) < 0)
	{
		mini->exec->return_value = 1;
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		mini->exec->return_value = 1;
		return ;
	}
	if (pid == 0)
	{
		args = ft_lstarg_in_tab(temp->arg);
		if (args == NULL)
		{
			close(fd[0]);
			close(fd[1]);
			mini->exec->return_value = 1;
			return ;
		}
		dup2(temp->infile_fd, 0);
		dup2(temp->outfile_fd, 1);
		close(temp->infile_fd);
		close(temp->outfile_fd);
		close(fd[0]);
		close(fd[1]);
		fork_execve_define_path(mini, temp, args);
	}
	if (temp->infile_fd != 0 && temp->infile_fd != 1)
		close(temp->infile_fd);
	if (temp->outfile_fd != 0 && temp->outfile_fd != 1)
		close(temp->outfile_fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &temp->return_value, 0);
}

int	execute_single_command(t_mini *mini)
{
	t_exec	*temp;

	temp = mini->exec;
	if (temp->arg && temp->arg->content)
	{
		if (check_built_in(temp->arg->content))
			exec_built_in(mini, temp->arg->content);
		else
			exec_single_case_function(mini, temp);
	}
	return (mini->exec->return_value);
}

void	single_command_case(t_mini *mini)
{
	t_exec	*temp;

	temp = mini->exec;
	if (mini->exec->redir)
		setup_redir(mini, temp);
	execute_single_command(mini);
	mini->last_return_value = mini->exec->return_value;
	return ;
}
