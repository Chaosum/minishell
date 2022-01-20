/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:39:04 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/19 14:31:46 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/get_next_line.h"

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

void	init_mini_struct(t_mini *mini, char **env)
{
	mini->exec = NULL;
	mini->last_return_value = 0;
	mini->token = NULL;
	if (init_mini_struct_env(mini, env) == -1)
		exit (1);
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
		free(content);
	}
	return (0);
}

void	sigint_handler(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_mini		mini;

	init_mini_struct(&mini, env);
	if (init_shell_level(&mini))
	{
		ft_free_env(&mini);
		return (1);
	}
	while (1)
	{
		signal(SIGINT, &sigint_handler);
		line = readline("$minishell> ");
		if (ft_strlen(line) > 0)
			add_history(line);
		if (line)
		{
			parsing(&mini, line);
			free(line);
		}
		else
			exit(130);
	}
	ft_free_env(&mini);
	return (1);
}
