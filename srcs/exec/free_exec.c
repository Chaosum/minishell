/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:42:55 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/31 20:54:43 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_pipe_tab(int *pipe_fd, int command_number, int mode)
{
	int	i;

	i = 0;
	if (pipe_fd)
	{
		while (i < command_number)
		{
			if (pipe_fd[i * 2] != 0 && pipe_fd[i * 2] != 1)
				close(pipe_fd[i * 2]);
			if (pipe_fd[i * 2 + 1] != 0 && pipe_fd[i * 2 + 1] != 1)
				close(pipe_fd[i * 2 + 1]);
			i++;
		}
	}
	if (mode)
	{
		signal(SIGINT, &sigint_handler_cat);
		signal(SIGQUIT, &sigint_handler_quit);
	}
}

void	free_lst_arg(t_mini *mini, t_arg *temp2)
{
	while (temp2)
	{
		free(temp2->content);
		temp2 = temp2->next;
		free(mini->exec->arg);
		mini->exec->arg = temp2;
	}
}

void	free_lst_redir(t_mini *mini, t_redir *temp3)
{
	while (temp3)
	{
		free(temp3->file);
		free(temp3->type);
		temp3 = temp3->next;
		free(mini->exec->redir);
		mini->exec->redir = temp3;
	}
}

void	free_lst_exec(t_mini *mini)
{
	t_exec	*temp;
	t_arg	*temp2;
	t_redir	*temp3;

	while (mini->exec)
	{
		temp = mini->exec->next;
		temp2 = mini->exec->arg;
		temp3 = mini->exec->redir;
		free_lst_arg(mini, temp2);
		free_lst_redir(mini, temp3);
		if (mini->exec->heredoc)
			free(mini->exec->heredoc);
		if (mini->exec->infile_fd != 0 && mini->exec->infile_fd != 1)
			close(mini->exec->infile_fd);
		if (mini->exec->outfile_fd != 1 && mini->exec->outfile_fd != 0)
			close(mini->exec->outfile_fd);
		free(mini->exec);
		mini->exec = temp;
	}
}
