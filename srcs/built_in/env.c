/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:50 by mservage          #+#    #+#             */
/*   Updated: 2022/02/02 04:34:07 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(t_env *env, t_mini *mini)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		write(mini->exec->outfile_fd, temp->value, ft_strlen(temp->value));
		write(mini->exec->outfile_fd, "\n", 1);
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
	ft_print_env(mini->env, mini);
	ft_free_tab(args);
	mini->exec->return_value = 0;
	return ;
}
