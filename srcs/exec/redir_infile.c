/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 01:46:40 by mservage          #+#    #+#             */
/*   Updated: 2021/09/30 02:42:40 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_check_opening_error(t_mini *mini, t_exec *exec)
{
	if (exec->redir->fd == -1 || errno == EACCES)
	{
		if (errno == EACCES)
			printf("Permission denied\n");
		else
			printf("No such file or directory\n");
		return (1);
	}
	return (0);
}

void	ft_redir_infile(t_mini *mini, t_exec *exec)
{
	exec->redir->fd = open(exec->redir->file, O_CREAT | O_RDONLY);
	if (redir_check_opening_error(mini, exec))
		exit(666);
	exec->index.infile = 1;
	exec->heredoc = 0;
	exec->infile_fd = exec->redir->fd;
}

void	ft_redir_outfile(t_mini *mini, t_exec *exec, int append)
{
	if (append == 0)
	{
		exec->redir->fd = open(exec->redir->file, O_CREAT | O_WRONLY | O_TRUNC);
		if (redir_check_opening_error(mini, exec))
			exit(666);
		exec->index.outfile++;
		exec->outfile_fd = exec->redir->fd;
	}
	if (append == 1)
	{
		exec->redir->fd = open(exec->redir->file,
				 O_CREAT | O_WRONLY | O_APPEND);
		if (redir_check_opening_error(mini, exec))
			exit(666);
		exec->index.outfile++;
		exec->outfile_fd = exec->redir->fd;
	}
}
