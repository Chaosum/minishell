/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:45:12 by matthieu          #+#    #+#             */
/*   Updated: 2021/09/28 17:48:08 by matthieu         ###   ########.fr       */
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

void	single_command_case(t_mini *mini)
{
	if (mini->exec)
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
