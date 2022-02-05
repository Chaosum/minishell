/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:48 by mservage          #+#    #+#             */
/*   Updated: 2022/02/03 14:49:47 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_free_all(t_mini *mini, int exit_value, char **args)
{
	ft_free_tab(args);
	free_lst_exec(mini);
	ft_free_env(mini);
	exit(exit_value);
}

int	ft_atol(const char *str)
{
	int					i;
	unsigned long int	a;
	int					neg;

	i = 0;
	a = 0;
	neg = 1;
	while ((str[i] >= 9) && ((str[i] <= 13) || (str[i] == 32)))
		i++;
	if ((str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (((str[i] >= '0') && (str[i] <= '9')) && (str[i]))
		a = a * 10 + (str[i++] - '0');
	if ((a > 2147483647) && (neg > 0))
		return (1);
	else if ((a > 2147483648) && (neg < 0))
		return (1);
	return (0);
}

int	check_valid_args_exit(char **args)
{
	int	j;

	j = 0;
	if (args[1])
	{
		if (args[1][0] == '-')
			j++;
		while (args[1][j] && ft_isdigit(args[1][j]))
			j++;
		if (j == (int)ft_strlen(args[1]))
			return (1);
		if (ft_atol(args[1]))
			return (0);
		return (0);
	}
	return (1);
}

void	ft_exit(t_mini *mini, t_arg *prms)
{
	char			**args;
	long int		exit_value;

	exit_value = 1;
	args = ft_lstarg_in_tab(prms);
	if (check_valid_args_exit(args) == 0)
	{
		write(2, "exit\nexit: numeric argument required\n", 38);
		ft_exit_free_all(mini, 255, args);
	}
	if (ft_tab_size(args) > 2)
	{
		write(2, "exit\nexit: too many arguments\n", 31);
		ft_free_tab(args);
		mini->exec->return_value = 1;
		return ;
	}
	write(2, "exit\n", 6);
	if (args[1])
		exit_value = ft_atoi(args[1]);
	while (exit_value < 0)
		exit_value += 256;
	exit_value = exit_value % 256;
	ft_exit_free_all(mini, exit_value, args);
}
