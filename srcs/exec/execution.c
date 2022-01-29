/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:04:41 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/29 17:02:56 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*define_command_path(char *path, char *command)
{
	char	*dest;
	int		i;
	int		j;

	dest = ft_calloc(ft_strlen(path) + ft_strlen(command) + 2, sizeof(char));
	i = 0;
	j = 0;
	if (dest == NULL)
		return (NULL);
	while (path[i])
	{
		dest[j] = path[i];
		j++;
		i++;
	}
	dest[j++] = '/';
	i = 0;
	while (command[i] != 0)
	{
		dest[j] = command[i];
		j++;
		i++;
	}
	return (dest);
}

int	fork_execve_define_path(t_mini *mini, t_exec *temp, char **args)
{
	int		i;
	char	*command_path;
	char	**path;

	path = NULL;
	command_path = NULL;
	i = 0;
	if (ft_strncmp(args[0], "/", 1) == 0
		|| ft_strncmp(args[0], "./", 2) == 0)
		execve(args[0], args, NULL);
	else
	{
		path = define_env_path(mini);
		if (path)
		{
			while (path[i])
			{
				command_path = define_command_path(path[i], args[0]);
				execve(command_path, args, NULL);
				i++;
				free(command_path);
			}
		}
	}
	temp->return_value = 1;
	write(2, "Command not found : ", 21);
	write(2, args[0], ft_strlen(args[0]));
	write(2, "\n", 1);
	if (path)
		ft_free_tab(path);
	if (args)
		ft_free_tab(args);
	free_lst_exec(mini);
	clear_history();
	exit (1);
}
