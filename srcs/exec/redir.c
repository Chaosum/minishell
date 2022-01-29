/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:48:09 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/29 15:51:45 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_redir(t_mini *mini, t_exec *temp)
{
	t_redir	*temp_redir;

	temp_redir = temp->redir;
	while (temp_redir)
	{
		if (ft_strncmp(temp_redir->type, "<<", 3) == 0)
			ft_heredoc(mini, temp, temp_redir);
		else if (ft_strncmp(temp_redir->type, "<", 2) == 0)
			ft_redir_infile(temp, temp_redir);
		else if (ft_strncmp(temp_redir->type, ">", 2) == 0)
			ft_redir_outfile(temp, temp_redir, 0);
		else if (ft_strncmp(temp_redir->type, ">>", 3) == 0)
			ft_redir_outfile(temp, temp_redir, 1);
		if (temp->heredoc_error)
			return ;
		temp_redir = temp_redir->next;
	}
}
