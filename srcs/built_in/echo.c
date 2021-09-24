/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:52 by mservage          #+#    #+#             */
/*   Updated: 2021/09/24 16:16:17 by mservage         ###   ########.fr       */
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

void	ft_echo(int ac, char **av)
{
	int	n_arg;

	n_arg = check_echo_arg(av);
	if (n_arg)
	{
		printf("%s", av[2]);
	}
}
