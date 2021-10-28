/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:48 by mservage          #+#    #+#             */
/*   Updated: 2021/10/27 23:59:12 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_free_all(t_mini *mini, int exit_value)
{
	free_lst_exec(mini);
	ft_free_env(mini);
	exit(exit_value);
}

void	ft_exit(t_mini *mini, t_arg *prms)
{
	char			**args;
	long int		exit_value;

	exit_value = 1;
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
	if (args[1])
		exit_value = ft_atoi(args[1]);
	if (exit_value < 0)
	{
		exit_value = 255;
		write(2, "exit: numeric argument required\n", 33);
	}
	exit_value = exit_value % 256;
	ft_free_tab(args);
	ft_exit_free_all(mini, exit_value);
}
