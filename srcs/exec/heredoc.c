/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:23:56 by mservage          #+#    #+#             */
/*   Updated: 2022/01/29 16:44:38 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_pipe(t_redir *temp_redir, int fd[2])
{
	char	*line;
	char	*temp;
	char	*input;

	input = ft_strdup("");
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
		{
			printf("Warning heredoc ended with EOF instead of %s\n",
				temp_redir->file);
			break ;
		}
		if (ft_strncmp(line, temp_redir->file,
				ft_strlen(temp_redir->file)) == 0)
			break ;
		temp = ft_strjoin(input, line);
		free(line);
		free(input);
		input = ft_strjoin(temp, "\n");
		free(temp);
	}
	write(fd[1], input, ft_strlen(input) + 1);
	free(input);
	free(line);
}



void	free_mini_heredoc(t_mini *mini)
{
	if (mini->exec)
	{
		free_lst_exec(mini);
	}
}

void	heredoc_fork(t_mini *mini, int fd[2], t_redir *temp_redir)
{
	signal(SIGINT, &sigint_handler_heredoc);
	heredoc_pipe(temp_redir, fd);
	close(fd[0]);
	close(fd[1]);
	free_mini_heredoc(mini);
	exit(0);
	return ;
}

void	ft_heredoc(t_mini *mini, t_exec *temp_exec, t_redir *temp_redir)
{
	int		fd[2];
	pid_t	pid;
	char	buf[2];
	char	*temp;

	temp = NULL;
	buf[1] = 0;
	pipe(fd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		heredoc_fork(mini, fd, temp_redir);
	waitpid(pid, &mini->last_return_value, 0);
	read(fd[0], buf, 1);
	while (buf[0] != 0 && mini->last_return_value == 0)
	{
		temp = ft_strjoin(temp_exec->heredoc, buf);
		free(temp_exec->heredoc);
		temp_exec->heredoc = ft_strdup(temp);
		free(temp);
		read(fd[0], buf, 1);
	}
	if (temp_exec->heredoc == NULL)
		temp_exec->heredoc = ft_strdup("");
	if (mini->last_return_value)
		temp_exec->heredoc_error = 1;
	close(fd[0]);
	close(fd[1]);
	temp_exec->index.heredoc = 1;
	temp_exec->index.infile = 0;
}
