/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:09:03 by matthieu          #+#    #+#             */
/*   Updated: 2021/09/10 14:08:21 by matthieu         ###   ########.fr       */
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

char	*get_env_var(char *get, char **env)
{
	char	*dest;
	int		i;

	dest = NULL;
	i = 0;
	while (env[i] && ft_strncmp(get, env[i], ft_strlen(get)))
		i++;
	dest = env[i];
	return (dest);
}

void	ft_free_all(t_malloc malloced)
{
	int	i;

	i = 0;
	while (malloced.env[i])
		free(malloced.env[i++]);
	free(malloced.env);
}

int	ft_error_exit(char *msg, t_mini *mini)
{
	printf("%s\n", msg);
	ft_free_all(mini->malloced);
	exit(1);
	return (1);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}
