/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:37:10 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/02 15:52:47 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_free_env(t_mini *mini)
{
	t_env	*temp;

	while (mini->env)
	{
		free(mini->env->value);
		temp = mini->env->next;
		free(mini->env);
		mini->env = temp;
	}
}

int	init_mini_struct_env(t_mini *mini, char **env)
{
	t_env	*temp;
	int		i;

	i = 0;
	mini->env = NULL;
	while (env[i])
	{
		temp = ft_calloc(1, sizeof(t_env));
		if (temp == NULL)
		{
			i = -1;
			break ;
		}
		temp->value = ft_strdup(env[i]);
		if (temp->value == NULL)
		{
			i = -1;
			break ;
		}
		ft_lstadd_back_env(&mini->env, temp);
		i++;
	}
	if (i == -1)
		ft_free_env(mini);
	return (i);
}

int	init_shell_level(t_mini *mini)
{
	t_env	*temp;
	int		value;
	char	*content;

	temp = get_env_var("SHLVL", mini);
	if (temp == NULL)
		ft_add_env_var("SHLVL=1", mini);
	else
	{
		value = ft_atoi(&temp->value[6]);
		if (value < 0)
			value = 0;
		value++;
		if (value > 999)
			value = 0;
		content = ft_itoa(value);
		if (content == NULL)
			return (1);
		change_env_var_value(temp, content);
		free(content);
	}
	return (0);
}

int	init_mini_struct(t_mini *mini, char **env)
{
	mini->exec = NULL;
	mini->last_return_value = 0;
	mini->token = NULL;
	if (init_mini_struct_env(mini, env) == -1)
	{
		printf("Exit : malloc error\n");
		exit(1);
	}
	if (init_shell_level(mini))
	{
		printf("Exit : malloc error\n");
		ft_free_env(mini);
		return (1);
	}
	return (0);
}
