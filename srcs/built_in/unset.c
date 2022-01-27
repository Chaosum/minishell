/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:41 by mservage          #+#    #+#             */
/*   Updated: 2022/01/27 14:56:45 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_var(t_mini *mini, t_env *temp, t_env *previous)
{
	if (previous)
		previous->next = temp->next;
	else
		mini->env = temp->next;
	free(temp->value);
	free(temp);
	return ;
}

void	ft_remove_env(t_mini *mini, char *arg)
{
	t_env	*temp;
	t_env	*previous;
	int		i;

	i = 0;
	previous = NULL;
	temp = mini->env;
	while (temp)
	{
		if (ft_strncmp(temp->value, arg, ft_strlen(arg)) == 0)
		{
			delete_var(mini, temp, previous);
			return ;
		}
		previous = temp;
		temp = temp->next;
	}
}

int	check_if_correct_unset(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(t_mini *mini, t_arg *prms)
{
	char	**args;
	int		i;
	int		error;

	i = 0;
	error = 0;
	args = ft_lstarg_in_tab(prms);
	while (args[i])
	{
		if (check_if_correct_unset(args[i]) == 0)
			ft_remove_env(mini, args[i]);
		i++;
	}
	mini->exec->return_value = error;
	ft_free_tab(args);
	return ;
}
