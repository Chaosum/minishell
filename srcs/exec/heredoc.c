/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:23:56 by mservage          #+#    #+#             */
/*   Updated: 2022/01/26 16:07:45 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_pipe(t_exec *temp2, int fd[2])
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
		free(temp);
	}
	write(fd[1], input, ft_strlen(input) + 1);
	free(input);
	free(line);
}

void	sigint_handler_heredoc(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(130);
}

void	free_mini_heredoc(t_mini *mini)
{
	if (mini->exec)
	{
		free_lst_exec(mini);
	}
}

void	heredoc_fork(t_mini *mini, t_exec *temp2, int fd[2])
{
	signal(SIGINT, &sigint_handler_heredoc);
	heredoc_pipe(temp2, fd);
	close(fd[0]);
	close(fd[1]);
	free_mini_heredoc(mini);
	exit(0);
	return ;
}

void	ft_heredoc(t_mini *mini, t_exec *temp2)
{
	int		fd[2];
	pid_t	pid;
	char	buf[2];
	char	*temp;
	int		wstatus;

	temp = NULL;
	buf[1] = 0;
	pipe(fd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		heredoc_fork(mini, temp2, fd);
	waitpid(pid, &mini->last_return_value, 0);
	read(fd[0], buf, 1);
	while (buf[0] != 0 && mini->last_return_value == 0)
	{
		temp = ft_strjoin(temp2->heredoc, buf);
		free(temp2->heredoc);
		temp2->heredoc = ft_strdup(temp);
		free(temp);
		read(fd[0], buf, 1);
	}
	if (temp2->heredoc == NULL)
		temp2->heredoc = ft_strdup("");
	if (mini->last_return_value)
		temp2->heredoc_error = 1;
	close(fd[0]);
	close(fd[1]);
	temp2->index.heredoc = 1;
	printf("END |%s|", temp2->heredoc);
}
