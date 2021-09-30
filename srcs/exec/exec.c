/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:45:12 by matthieu          #+#    #+#             */
/*   Updated: 2021/09/30 04:28:26 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lst_size_exec(t_exec	*exec)
{
	t_exec	*temp;
	int		i;

	i = 0;
	temp = exec;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

int	execute_command(t_mini *mini)
{
}

void	single_command_case(t_mini *mini)
{
	t_exec	*temp;

	temp = mini->exec;
	if (mini->exec->redir)
	{
		while (temp->redir)
		{
			if (ft_strncmp(mini->exec->redir->type, "heredoc",
					ft_strlen("heredoc")))
				ft_heredoc(mini, temp);
			else if (ft_strncmp(mini->exec->redir->type, "<"))
				ft_redir_infile(mini, temp);
			else if (ft_strncmp(mini->exec->redir->type, ">"))
				ft_redir_outfile(mini, temp, 0);
			else if (ft_strncmp(mini->exec->redir->type, ">>"))
				ft_redir_outfile(mini, temp, 1);
			temp->redir = temp->redir->next;
		}
	}
	execute_command(mini);
}

void	ft_execution(t_mini *mini)
{
	t_exec	*start;
	int		command_number;

	start = mini->exec;
	command_number = ft_lst_size_exec(mini->exec);
	if (command_number == 0)
		return (1);
	else if (command_number == 1)
		single_command_case(mini);
	else if (command_number > 1)
		multiple_command_case(mini, command_number);
	return (0);
}
