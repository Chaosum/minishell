/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:50 by mservage          #+#    #+#             */
/*   Updated: 2021/10/13 01:54:43 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		printf("%s\n", temp->value);
		temp = temp->next;
	}
}

void	ft_env(t_mini *mini, t_arg *prms)
{
	char	**args;

	args = ft_lstarg_in_tab(prms);
	if (ft_tab_size(args) > 1)
	{
		write(2, "env: too many arguments\n", 25);
		ft_free_tab(args);
		mini->exec->return_value = 1;
		return ;
	}
	ft_print_env(mini->env);
	mini->exec->return_value = 0;
	return ;
}
