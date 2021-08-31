/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:39:04 by matthieu          #+#    #+#             */
/*   Updated: 2021/08/31 15:07:18 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *line, char **env)
{
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;

	line = NULL;
	prompt = "$minishell>";
	while (1)
	{
		line = readline(prompt);
		parsing(line, env);
	}
	return (1);
}
