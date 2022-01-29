/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:55:01 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/29 16:42:08 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

void	exec_built_in(t_mini *mini, char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(mini, mini->exec->arg);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		ft_cd(mini, mini->exec->arg);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(mini);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(mini, mini->exec->arg);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ft_export(mini, mini->exec->arg);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ft_unset(mini, mini->exec->arg);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		ft_exit(mini, mini->exec->arg);
}
