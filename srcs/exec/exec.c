/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:45:12 by matthieu          #+#    #+#             */
/*   Updated: 2021/10/13 02:16:12 by mservage         ###   ########.fr       */
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

int	check_built_in(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

void	exec_built_in(t_mini *mini, char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(mini, mini->exec->arg);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		ft_cd(mini, mini->exec->arg);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(mini, mini->exec->arg);
	if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(mini, mini->exec->arg);
	if (ft_strncmp(cmd, "export", 7) == 0)
		ft_export(mini, mini->exec->arg);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		ft_unset(mini, mini->exec->arg);
}

int	execute_command(t_mini *mini)
{
	t_exec	*temp;

	temp = mini->exec;
	if (temp->arg && temp->arg->content)
	{
		if (check_built_in(temp->arg->content))
			exec_built_in(mini, temp->arg);
	}
	mini->exec->return_value = 0;
	return (mini->exec->return_value);
}

void	single_command_case(t_mini *mini)
{
	t_exec	*temp;

	temp = mini->exec;
	if (mini->exec->redir)
	{
		while (temp && temp->redir)
		{
			if (ft_strncmp(mini->exec->redir->type, "<<",
					ft_strlen("<<")))
				ft_heredoc(mini, temp);
			else if (ft_strncmp(mini->exec->redir->type, "<", 2))
				ft_redir_infile(mini, temp);
			else if (ft_strncmp(mini->exec->redir->type, ">", 2))
				ft_redir_outfile(mini, temp, 0);
			else if (ft_strncmp(mini->exec->redir->type, ">>", 3))
				ft_redir_outfile(mini, temp, 1);
			temp->redir = temp->redir->next;
		}
	}
	execute_command(mini);
	return ;
}

void	ft_execution(t_mini *mini)
{
	int		command_number;

	mini->start_exec = mini->exec;
	command_number = ft_lst_size_exec(mini->exec);
	if (command_number == 0)
		return (1);
	else if (command_number == 1)
		single_command_case(mini);
	else if (command_number > 1)
		multiple_command_case(mini, command_number);
	return (0);
}
