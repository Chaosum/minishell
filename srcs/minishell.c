/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:39:04 by matthieu          #+#    #+#             */
/*   Updated: 2021/10/27 02:47:19 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_mini_struct_env(t_mini *mini, char **env)
{
	t_env	*temp;
	int		i;

	i = 0;
	mini->env = NULL;
	while (env[i])
	{
		temp = ft_calloc(1, sizeof(t_env));
		if (temp == NULL)
			exit(666);
		temp->value = ft_strdup(env[i]);
		if (temp->value == NULL)
			exit(666);
		ft_lstadd_back_env(&mini->env, temp);
		i++;
	}
}

void	init_mini_struct(t_mini *mini, char **env)
{
	mini->exec = NULL;
	mini->last_return_value = 0;
	init_mini_struct_env(mini, env);
}

int	parsing(t_mini *mini, char *line)
{
	ft_execution(mini);
	return (0);
}

int	init_shell_level(t_mini *mini)
{
	t_env	*temp;
	int		value;
	char	*content;

	temp = get_env_var("SHLVL=", mini);
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
		change_env_var_value(mini, temp, content);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	char		*prompt;
	t_mini		mini;

	init_mini_struct(&mini, env);
	if (init_shell_level(&mini))
	{
		free(mini.env);
		return (1);
	}
	line = NULL;
	prompt = "$minishell> ";
	while (1)
	{
		line = readline(prompt);
		add_history(line);
		parsing(&mini, line);
	}
	return (1);
}
