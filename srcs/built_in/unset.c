/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:41 by mservage          #+#    #+#             */
/*   Updated: 2021/10/14 05:13:01 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))
		return (1);
	return (0);
}

int	check_if_correct_unset(t_mini *mini, char *arg, int *error)
{
	int			valid;
	int			i;

	i = 0;
	valid = 1;
	while (arg[i] && valid == 1 && arg[0] != '=')
	{
		if ((ft_isalpha(arg[i]) == 0) && valid == 0)
		{
			if (*error == 0)
				write(2, "unset: invalid parameter name\n", 31);
			error = 1;
			return (1);
		}
		if (arg[i] == '=')
			valid = 0;
	}
	if (arg[0] == '=')
	{
		*error = 1;
		write(2, "unset: invalid parameter name\n", 31);
	}
	return (valid);
}

void	delete_var(t_mini *mini, t_env *temp, t_env *previous)
{
	if (previous)
		previous->next = temp->next;
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
	while (arg[i] != '=' && arg[i])
		i++;
	if (arg[i] == '=')
		i++;
	while (temp)
	{
		if (ft_strncmp(temp->value, arg, i) == 0)
		{
			delete_var(mini, temp, previous);
			return ;
		}
		previous = temp;
		temp = temp->next;
	}
}

void	ft_unset(t_mini *mini, t_arg *prms)
{
	char	**args;
	int		i;
	int		j;
	int		error;

	i = 0;
	error = 0;
	args = ft_lstarg_in_tab(prms);
	while (args[i])
	{
		if (check_if_correct_unset(mini, args[i], &error) == 0)
			ft_remove_env(mini, args[i]);
		i++;
	}
	mini->exec->return_value = error;
	ft_free_tab(args);
	return ;
}
