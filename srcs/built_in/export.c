/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:45 by mservage          #+#    #+#             */
/*   Updated: 2021/10/14 04:47:51 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_valid_var(char *arg, int *error)
{
	int			valid;
	int			i;

	i = 0;
	valid = 1;
	while (arg[i] && valid == 1 && arg[0] != '=')
	{
		if (ft_isalpha(arg[i]) == 0 && valid == 0)
		{
			if (*error == 0)
				write(2, "export: not valid in this context\n", 35);
			*error = 1;
			return (1);
		}
		if (arg[i] == '=')
			valid = 0;
	}
	if (arg[0] == '=')
	{
		*error = 1;
		write(2, "zsh: bad assignment\n", 21);
	}
	return (valid);
}

int	check_already_exist(t_mini *mini, char *args)
{
	char	*var[PATH_MAX];
	int		i;
	t_env	*temp;

	temp = mini->env;
	i = 0;
	while (args[i] && i < PATH_MAX - 1 && args[i] != '=')
	{
		var[i] = args[i];
		i++;
	}
	if (args[i] == '=')
		i++;
	var[i] = 0;
	while (temp)
	{
		if (ft_strncmp(temp->value, var, ft_strlen(var)) == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	modify_existing_var(t_mini *mini, char *args)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = mini->env;
	while (args[i] != '=' && args[i])
		i++;
	if (args[i] == '=')
		i++;
	while (temp)
	{
		if (ft_strncmp(args, temp->value, i) == 0)
		{
			change_env_var_value(mini, temp, &args[i]);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

void	ft_export(t_mini *mini, t_arg *prms)
{
	char	**args;
	int		error;
	int		i;

	args = ft_lstarg_in_tab(prms);
	i = 1;
	error = 0;
	while (args[i])
	{
		if (check_if_valid_var(args[i], &error) == 0)
		{
			if (check_already_exist(mini, args[i]))
				ft_add_env_var(args[i], mini);
			else if (check_already_exist(mini, args[i]) == 0)
				modify_existing_var(mini, args[i]);
		}
		i++;
	}
	mini->exec->return_value = error;
	ft_free_tab(args);
	return ;
}
