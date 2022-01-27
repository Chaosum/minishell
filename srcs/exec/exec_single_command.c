/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:29:08 by mservage          #+#    #+#             */
/*   Updated: 2022/01/27 18:13:48 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler_cat(int signum)
{
	if (signum)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	sigint_handler_quit(int signum)
{
	if (signum)
	{
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

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
	if (temp->heredoc)
	{
		temp->infile_fd = fd[0];
		write(fd[1], temp->heredoc, ft_strlen(temp->heredoc));
	}
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		mini->exec->return_value = 1;
		return ;
	}
	signal(SIGINT, &sigint_handler_cat);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
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
		if (temp->infile_fd != 0 && temp->infile_fd != 1)
			close(temp->infile_fd);
		if (temp->outfile_fd != 0 && temp->outfile_fd != 1)
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
	if (temp->heredoc_error == 0)
	{
		execute_single_command(mini);
		mini->last_return_value = mini->exec->return_value;
	}
	else
		return ;
	return ;
}
