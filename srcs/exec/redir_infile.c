/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 01:46:40 by mservage          #+#    #+#             */
/*   Updated: 2022/01/27 19:16:09 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_check_opening_error(t_redir *temp_redir)
{
	if (temp_redir->fd == -1 || errno == EACCES)
	{
		if (errno == EACCES)
			printf("Permission denied\n");
		else
			printf("No such file or directory : %s\n", temp_redir->file);
		return (1);
	}
	return (0);
}

void	ft_redir_infile(t_exec *exec, t_redir *temp_redir)
{
	if (exec->outfile_fd != 1 && exec->outfile_fd != 0)
		close(exec->infile_fd);
	temp_redir->fd = open(temp_redir->file, O_RDONLY);
	if (redir_check_opening_error(temp_redir))
		exit(666);//
	exec->index.infile = 1;
	exec->index.heredoc = 0;
	exec->infile_fd = temp_redir->fd;
}

void	ft_redir_outfile(t_exec *exec, t_redir *temp_redir, int append)
{
	if (exec->outfile_fd != 1 && exec->outfile_fd != 0)
		close(exec->outfile_fd);
	if (append == 0)
	{
		temp_redir->fd = open(temp_redir->file,
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (redir_check_opening_error(temp_redir))
			exit(666);
		exec->index.outfile++;
		exec->outfile_fd = temp_redir->fd;
	}
	if (append == 1)
	{
		temp_redir->fd = open(temp_redir->file,
				O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (redir_check_opening_error(temp_redir))
			exit(666);
		exec->index.outfile = 1;
		exec->outfile_fd = temp_redir->fd;
	}
}
