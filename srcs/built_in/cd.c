/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:54 by mservage          #+#    #+#             */
/*   Updated: 2021/10/11 15:47:29 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	t_arg_number_content(t_arg *temp)
{
	int	i;

	i = 0;
	while (temp && temp->content)
	{
		temp = temp->next;
		i++;
	}	
	return (i);
}

char	**ft_lstarg_in_tab(t_arg *prms)
{
	char	**dest;
	int		i;
	t_arg	*temp;

	temp = prms;
	i = t_arg_number_content(prms);
	dest = ft_calloc(sizeof(char *), i + 1);
	if (dest == NULL)
		exit (666);
	while (temp && temp->content)
	{
		dest = ft_strdup(temp->content);
		if (dest == NULL)
			exit (666);
		temp = temp->next;
	}
	return (dest);
}

void	change_oldpwd(t_mini *mini)
{
	change_env_var_value(mini, get_env_var("OLDPWD", mini),
		&get_env_var("PWD", mini)->value[5]);
}

void	change_pwd(t_mini *mini)
{
	change_env_var_value(mini, get_env_var("PWD", mini),
		&get_env_var("HOME", mini)->value[6]);
}

void	cd_no_arg(t_mini *mini)
{
	char	*path;

	if (get_env_var("HOME", mini)->value == NULL)
	{
		write(2, "cd: « HOME » non défini", 27);
		mini->exec->return_value = 1;
		return ;
	}
	change_oldpwd(mini);
	change_pwd(mini);
	path = &get_env_var("PWD", mini)->value[5];
	mini->exec->return_value = chdir(path);
	return ;
}

void	trim_last_path(char *content, int start)
{
	int	i;

	i = start;
	while (content[i])
		i++;
	i--;
	while (content[i] != '/' && i > start)
	{
		content[i] = 0;
		i--;
	}
}

void	ft_cd_path(t_mini *mini, char **args)
{
	if (ft_strncmp(".", args[1], 2) == 0 || ft_strncmp("./", args[1], 3) == 0)
	{
		change_oldpwd(mini);
		mini->exec->return_value = 0;
		return ;
	}
	else if (ft_strncmp("..", args[1], 3) == 0
		|| ft_strncmp("../", args[1], 2) == 0)
	{
		change_oldpwd(mini);
		trim_last_path(get_env_var("PWD", mini)->value, 5);
		mini->exec->return_value = chdir(&get_env_var("PWD", mini)->value[5]);
		return ;
	}
}

void	ft_cd(t_mini *mini, t_arg *prms)
{
	char	**args;

	args = ft_lstarg_in_tab(prms);
	if (ft_tab_size(args) > 1)
	{
		write(2, "cd: trop d'arguments", 21);
		mini->exec->return_value = 1;
		return ;
	}
	get_env_var("HOME", mini)->value;
	if (!args[1])
		return (cd_no_arg(mini));
	if (args[1][0] == 0)
	{
		change_oldpwd(mini);
		mini->exec->return_value = 0;
		return ;
	}
	else
		ft_cd_path(mini, args);
}
