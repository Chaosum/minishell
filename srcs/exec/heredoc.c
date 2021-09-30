/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:23:56 by mservage          #+#    #+#             */
/*   Updated: 2021/09/30 02:38:29 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_heredoc(t_mini *mini, t_exec *temp)
{
	char	*input;
	char	*line;
	char	*temp;

	input = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			exit(666);
		if (ft_strncmp(line, temp->redir->file, ft_strlen(temp->redir->file)))
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
	temp->heredoc = 1;
	temp->heredoc = input;
}
