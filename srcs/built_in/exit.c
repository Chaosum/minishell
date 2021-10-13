/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:48 by mservage          #+#    #+#             */
/*   Updated: 2021/10/13 02:16:48 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_free_all(t_mini *mini)
{
	while (mini->start_exec)
	{
		if (mini->exec)
		{
			if (mini->exec->redir)
				free_redir_lst(mini->exec->redir);
			if (mini->exec->arg)
				free_arg_lst(mini->exec->arg);
			if (mini->exec->heredoc)
				free(mini->exec->heredoc);
			close(mini->exec->infile_fd);
			close(mini->exec->outfile_fd);
			free(mini->exec);
		}
		mini->start_exec = mini->start_exec->next;
	}
	ft_free_env(mini->env);
	exit(0);
}

void	ft_exit(t_mini *mini, t_arg *prms)
{
	char	**args;

	args = ft_lstarg_in_tab(prms);
	if (ft_tab_size(args) > 1)
	{
		write(2, "exit\n", 6);
		write(2, "env: too many arguments\n", 25);
		ft_free_tab(args);
		mini->exec->return_value = 1;
		return ;
	}
	write(2, "exit\n", 6);
	ft_free_tab(args);
	ft_exit_free_all(mini);
}
