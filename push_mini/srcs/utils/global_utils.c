/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:09:03 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/03 14:24:35 by mservage         ###   ########.fr       */
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

int	cmp_equa(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s2[i] && s2[i] != '=')
		{
			if (s1[i] - s2[i])
				return (1);
			i++;
		}
		if (s2[i] == '=' && !s1[i])
			return (0);
		else
			return (1);
	}
	return (1);
}

t_env	*get_env_var(char *get, t_mini *mini)
{
	t_env	*temp;

	temp = mini->env;
	while (temp)
	{
		if (!cmp_equa(get, temp->value))
		{
			return (temp);
		}
		temp = temp->next;
	}
	return (NULL);
}

void	ft_add_env_var(char *value, t_mini *mini)
{
	t_env	*temp;

	temp = ft_calloc(1, sizeof(t_env));
	temp->value = ft_strdup(value);
	ft_lstadd_back_env(&mini->env, temp);
}

void	change_env_var_value(t_env *var, char *content)
{
	char	*temp;
	int		i;

	i = 0;
	while (var->value[i] != '=' && var->value[i])
		i++;
	temp = ft_calloc(i + ft_strlen(content) + 2, sizeof(char));
	if (temp == NULL)
		return ;
	i = 0;
	while (var->value[i] != '=' && var->value[i])
	{
		temp[i] = var->value[i];
		i++;
	}
	temp[i] = var->value[i];
	ft_strlcat(temp, content, i + ft_strlen(content) + 2);
	free(var->value);
	var->value = temp;
}
