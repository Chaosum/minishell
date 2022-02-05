/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:29:08 by mservage          #+#    #+#             */
/*   Updated: 2022/02/04 15:27:03 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_single_case_function_fork(t_mini *mini, t_exec *temp,
		char **args, int fd[2])
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	args = ft_lstarg_in_tab(temp->arg);
	if (args == NULL)
	{
		close_all_fd(fd[0], fd[1], NULL);
		mini->exec->return_value = 1;
		return ;
	}
	dup2(temp->infile_fd, 0);
	dup2(temp->outfile_fd, 1);
	if (temp->infile_fd != 0 && temp->infile_fd != 1)
		close(temp->infile_fd);
	if (temp->outfile_fd != 0 && temp->outfile_fd != 1)
		close(temp->outfile_fd);
	close_all_fd(fd[0], fd[1], NULL);
	fork_execve_define_path(mini, args);
}

void	exec_heredoc_write(t_exec *temp, int fd[2])
{
	temp->infile_fd = fd[0];
	write(fd[1], temp->heredoc, ft_strlen(temp->heredoc));
}

void	close_all_fd(int ffd, int sfd, t_exec *temp)
{
	char buf[5];
	if (temp)
	{
		if (temp->infile_fd != 0 && temp->infile_fd != 1)
			close(temp->infile_fd);
		if (temp->outfile_fd != 0 && temp->outfile_fd != 1)
			close(temp->outfile_fd);
	}
	if (ffd != 0 && ffd != 1)
		close(ffd);
	if (sfd != 0 && sfd != 1)
		close(sfd);
		dprintf(2, "ffd = %d sfd = %d\n", ffd, sfd);
		read(0, buf, 1);
}

void	exec_single_case_function(t_mini *mini, t_exec *temp, char **args)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
	{
		mini->exec->return_value = 1;
		return ;
	}
	if (temp->heredoc)
		exec_heredoc_write(temp, fd);
	pid = fork();
	if (pid < 0)
	{
		close_all_fd(fd[0], fd[1], NULL);
		mini->exec->return_value = 1;
		return ;
	}
	signal(SIGINT, &sigint_handler_cat);
	if (pid == 0)
		exec_single_case_function_fork(mini, temp, args, fd);
	close_all_fd(fd[0], fd[1], temp);
	signal(SIGINT, &sigint_handler_cat);
	signal(SIGQUIT, &sigint_handler_quit);
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
			exec_single_case_function(mini, temp, NULL);
	}
	return (mini->exec->return_value);
}
