/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:09:03 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/27 14:54:36 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tab_size(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			i++;
	}
	return (i);
}

t_env	*get_env_var(char *get, t_mini *mini)
{
	t_env	*temp;

	temp = mini->env;
	while (temp)
	{
		if (!ft_strncmp(get, temp->value, ft_strlen(get)))
			break ;
		temp = temp->next;
	}
	return (temp);
}

void	ft_add_env_var(char *value, t_mini *mini)
{
	t_env	*temp;

	temp = ft_calloc(1, sizeof(t_env));
	if (temp == NULL)
		exit(666);
	temp->value = ft_strdup(value);
	if (temp->value == NULL)
		exit(666);
	ft_lstadd_back_env(&mini->env, temp);
}

void	change_env_var_value(t_env *var, char *content)
{
	char	*temp;
	int		i;

	i = 0;
	while (var->value[i] != '=' && var->value[i])
		i++;
	temp = ft_calloc(i + ft_strlen(content) + 1, sizeof(char));
	if (temp == NULL)
		exit(666);
	i = 0;
	while (var->value[i] != '=' && var->value[i])
	{
		temp[i] = var->value[i];
		i++;
	}
	temp[i] = var->value[i];
	ft_strlcat(temp, content, i + ft_strlen(content));
	free(var->value);
	var->value = temp;
}
