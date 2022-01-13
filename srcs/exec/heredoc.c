/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:23:56 by mservage          #+#    #+#             */
/*   Updated: 2022/01/13 14:29:22 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_heredoc(t_mini *mini, t_exec *temp2)
{
	char	*input;
	char	*line;
	char	*temp;

	input = NULL;
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			exit(666);
		if (ft_strncmp(line, temp2->redir->file,
				ft_strlen(temp2->redir->file)) == 0)
			break ;
		temp = ft_strjoin(input, line);
		if (temp == NULL)
			exit(666);
		free(line);
		free(input);
		input = ft_strjoin(temp, "\n");
		if (input == NULL)
			exit (666);
	}
	free(line);
	temp2->index.heredoc = 1;
	temp2->heredoc = input;
}
/* redir */
