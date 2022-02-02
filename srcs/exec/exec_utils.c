/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:08:30 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/02 15:52:21 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_pipe_tab(int *pipe_fd, int command_number, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < 2048)
	{
		pipe_fd[i] = -1;
		pipe_fd[i] = -1;
		i++;
	}
	i = 0;
	while (i < command_number)
		pid[i++] = 0;
	if (verif_pipe_tab(command_number, pipe_fd))
		return (1);
	return (0);
}

char	**define_env_path(t_mini *mini)
{
	t_env	*temp;
	char	**dest;

	temp = get_env_var("PATH", mini);
	if (temp == NULL || temp->value == NULL)
		return (NULL);
	dest = ft_split(&temp->value[5], ':');
	if (dest == NULL)
		return (NULL);
	return (dest);
}

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
	dest = NULL;
	i = t_arg_number_content(prms);
	if (i > 0)
		dest = ft_calloc(sizeof(char *), i + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (temp && temp->content)
	{
		dest[i] = ft_strdup(temp->content);
		if (dest[i] == NULL)
		{
			ft_free_tab(dest);
			return (NULL);
		}
		temp = temp->next;
		i++;
	}
	return (dest);
}

int	ft_lst_size_exec(t_exec	*exec)
{
	t_exec	*temp;
	int		i;

	i = 0;
	if (exec)
	{
		temp = exec;
		while (temp)
		{
			temp = temp->next;
			i++;
		}
	}
	return (i);
}
