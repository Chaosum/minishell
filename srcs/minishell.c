/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:39:04 by matthieu          #+#    #+#             */
/*   Updated: 2021/11/17 13:42:58 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (init_mini_struct_env(mini, env) == -1)
		exit (1);
}

void	main_mini_temp(t_mini *mini)
{
	mini->exec = ft_calloc(1, sizeof(t_exec));
	mini->exec->infile_fd = 0;
	mini->exec->outfile_fd = 1;
	mini->exec->redir = NULL;
	mini->exec->arg = ft_calloc(1, sizeof(t_arg));
	mini->exec->arg->content = ft_strdup("echo");
	mini->exec->arg->next = ft_calloc(1, sizeof(t_arg));
	mini->exec->arg->next->content = ft_strdup("non");
	mini->exec->arg->next->next = ft_calloc(1, sizeof(t_arg));
	mini->exec->arg->next->next->content = ft_strdup("ouioui");
}

int	parsing(t_mini *mini, char *line)
{
	main_mini_temp(mini);
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
		free(content);
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
		ft_free_env(&mini);
		return (1);
	}
	line = NULL;
	prompt = "$minishell> ";
	// while (1)
	// {
	// 	line = readline(prompt);
	// 	add_history(line);
	parsing(&mini, line);
	// }
	ft_free_env(&mini);
	return (1);
}
