/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:54 by mservage          #+#    #+#             */
/*   Updated: 2021/10/13 01:53:43 by mservage         ###   ########.fr       */
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

void	change_oldpwd(t_mini *mini, char *old_path)
{
	t_env	*temp;
	char	path[PATH_MAX];

	temp = get_env_var("OLDPWD=", mini);
	if (temp == NULL)
	{
		ft_add_env_var("OLDPWD=", mini);
		temp = get_env_var("OLDPWD=", mini);
	}
	if (old_path == NULL)
		getcwd(path, PATH_MAX);
	else
		*path = old_path;
	change_env_var_value(mini, temp, path);
}

void	change_pwd(t_mini *mini, char *path)
{
	t_env	*temp;

	temp = get_env_var("PWD=", mini);
	mini->exec->redir = chdir(path);
	change_env_var_value(mini, temp, path);
	return ;
}

void	cd_no_arg(t_mini *mini)
{
	char	*path;

	if (get_env_var("HOME=", mini) == NULL
		|| get_env_var("HOME=", mini)->value == NULL)
	{
		write(2, "cd: « HOME » non défini", 27);
		mini->exec->return_value = 1;
		return ;
	}
	path = &get_env_var("HOME=", mini)->value[6];
	change_oldpwd(mini, NULL);
	change_pwd(mini, path);
	path = &get_env_var("PWD=", mini)->value[5];
	mini->exec->return_value = chdir(path);
	return ;
}

void	ft_cd_path(t_mini *mini, char **args)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	if (chdir(args[1]) == -1)
	{
		write(2, "cd: ", 4);
		write(2, &args[1], ft_strlen(args[1]));
		write(2, ": No such file or directory\n", 29);
		mini->exec->return_value = 1;
		return ;
	}
	change_oldpwd(mini, path);
	getcwd(path, PATH_MAX);
	change_pwd(mini, path);
	mini->exec->return_value = 0;
	return ;
}

void	ft_cd(t_mini *mini, t_arg *prms)
{
	char	**args;

	args = ft_lstarg_in_tab(prms);
	if (ft_tab_size(args) > 1)
	{
		write(2, "cd: too many arguments\n", 24);
		mini->exec->return_value = 1;
	}
	else if (!args[1])
		cd_no_arg(mini);
	else if (args[1][0] == 0)
	{
		change_oldpwd(mini, NULL);
		mini->exec->return_value = 0;
	}
	else
		ft_cd_path(mini, args);
	ft_free_tab(args);
	return ;
}
