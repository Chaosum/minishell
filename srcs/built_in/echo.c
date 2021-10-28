/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:52 by mservage          #+#    #+#             */
/*   Updated: 2021/10/28 04:02:33 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_print(char **args, t_mini *mini)
{
	int	i;

	i = 0;
	while (args[i])
	{
		write(mini->exec->outfile_fd, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(mini->exec->outfile_fd, " ", 1);
	}
	return ;
}

int	check_echo_arg(char **av)
{
	if (av[1])
	{
		if (ft_strncmp("-n", av[1], 3) == 0)
			return (1);
	}
	return (0);
}

void	ft_echo(t_mini *mini, t_arg *prms)
{
	char	**args;
	int		n_arg;

	args = ft_lstarg_in_tab(prms);
	if (args == NULL)
	{
		write(2, "Error\nMemory issue in echo\n", 28);
		mini->exec->return_value = 1;
		return ;
	}
	n_arg = check_echo_arg(args);
	if (n_arg)
	{
		if (args[2])
			echo_print(&args[2], mini);
	}
	else
	{
		if (args[1])
			echo_print(&args[1], mini);
		write(mini->exec->outfile_fd, "\n", 1);
	}
	mini->exec->return_value = 0;
	ft_free_tab(args);
	return ;
}
