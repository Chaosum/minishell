/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 23:33:15 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/29 16:13:23 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_pipe_command(t_mini *mini, t_exec *temp)
{
	char	**args;

	args = ft_lstarg_in_tab(temp->arg);
	if (args)
		fork_execve_define_path(mini, temp, args);
	return (1);
}

void	ft_wait_fork(pid_t *pid, int cmd_nbr)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < cmd_nbr)
	{
		waitpid(pid[i], &wstatus, 0);
		i++;
	}
}
