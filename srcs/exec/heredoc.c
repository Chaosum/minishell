/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:23:56 by mservage          #+#    #+#             */
/*   Updated: 2022/01/21 16:43:08 by matthieu         ###   ########.fr       */
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
		{
			printf("Warning heredoc ended with EOF instead of %s\n",
				temp2->redir->file);
			break ;
		}
		if (ft_strncmp(line, temp2->redir->file,
				ft_strlen(temp2->redir->file)) == 0)
			break ;
		temp = ft_strjoin(input, line);
		free(line);
		free(input);
		input = ft_strjoin(temp, "\n");
	}
	free(line);
	temp2->index.heredoc = 1;
	temp2->heredoc = input;
}
