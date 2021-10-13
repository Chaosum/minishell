/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:52 by mservage          #+#    #+#             */
/*   Updated: 2021/10/13 01:50:41 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_echo_arg(char **av)
{
	if (av[1])
	{
		if (ft_strncmp("-n", av[1], 3))
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
		return (1);
	}
	n_arg = check_echo_arg(args);
	if (n_arg)
	{
		if (args[2])
			printf("%s", args[2]);
	}
	else
	{
		if (args[1])
			printf("%s\n", args[1]);
		else
			printf("\n");
	}
	mini->exec->return_value = 0;
	ft_free_tab(args);
	return ;
}
