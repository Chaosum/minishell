/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:39:04 by matthieu          #+#    #+#             */
/*   Updated: 2021/09/10 13:58:17 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_mini_struct_malloced(t_mini *mini)
{
	mini->malloced.env = NULL;
}

void	init_mini_struct_env(t_mini *mini, char **env)
{
	int	i;

	i = 0;
	mini->env = NULL;
	mini->env = ft_calloc(ft_tab_size(env) + 1, sizeof(char *));
	if (mini->env == NULL)
		ft_error_exit("Memory error\n", mini);
	mini->malloced.env = mini->env;
	while (env[i])
	{
		mini->env[i] = ft_strdup(env[i]);
		if (mini->env[i] == NULL)
			ft_error_exit("Memory error\n", mini);
		i++;
	}
}

void	init_mini_struct(t_mini *mini, char **env)
{
	init_mini_struct_malloced(mini);
	init_mini_struct_env(mini, env);
}

/* free a verifier */

void	ft_add_env_var(t_mini *mini, char *env)
{
	int		i;
	int		j;
	int		size;
	char	**temp;
	char	**temp2;

	i = 0;
	j = 0;
	size = ft_tab_size(mini->env);
	temp = ft_calloc(size + 2, sizeof(char *));
	while (mini->env[i])
	{
		temp[i] = ft_strdup(mini->env[i]);
		if (temp[i] == NULL)
			ft_error_exit("Malloc error\n", mini);
		i++;
	}
	temp[i] = env;
	ft_free_tab(mini->env);
	mini->env = temp;
}

int	parsing(char *line, char **env)
{
	//input_execution(token, env);
	return (0);
}

/* free a verifier */

void	init_shell_level(t_mini *mini)
{
	char	*temp;
	int		value;
	char	*value_char;
	char	*temp2;

	temp = get_env_var("SHLVL", mini->env);
	if (temp == NULL)
		ft_add_env_var(mini, "SHLVL=1");
	else
	{
		value = ft_atoi(&temp[6]);
		value++;
		value_char = ft_itoa(value);
		if (value_char == NULL)
			ft_error_exit("Malloc error\n", mini);
		temp2 = ft_strjoin("SHLVL=", value_char);
		if (temp2 == NULL)
			ft_error_exit("Malloc error\n", mini);
		free(value_char);
		value_char = temp;
		temp = ft_strdup(temp2);
		if (temp == NULL)
			ft_error_exit("Malloc error\n", mini);
		free(temp2);
	}
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	char		*prompt;
	t_mini		mini;

	init_mini_struct(&mini, env);
	init_shell_level(&mini);
	line = NULL;
	prompt = "$minishell>";
	while (1)
	{
		line = readline(prompt);
		add_history(line);
		parsing(line, env);
	}
	return (1);
}
