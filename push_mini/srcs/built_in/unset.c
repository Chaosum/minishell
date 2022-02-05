/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:41 by mservage          #+#    #+#             */
/*   Updated: 2022/02/04 14:09:52 by mservage         ###   ########.fr       */
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

int	my_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s2[i] && (s1[i] - s2[i] == 0))
		{
			i++;
		}
		if (s1[i] == '=')
			return (1);
	}
	return (0);
}

void	ft_remove_env(t_mini *mini, char *arg)
{
	t_env	*temp;
	t_env	*previous;

	previous = NULL;
	temp = mini->env;
	while (temp)
	{
		if (my_strcmp(temp->value, arg))
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
		{
			printf("%s : not a valid identifier", args);
			return (1);
		}
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
		else
		{
			error = 1;
			break ;
		}
		i++;
	}
	mini->exec->return_value = error;
	ft_free_tab(args);
	return ;
}
