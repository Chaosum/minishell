/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:45:12 by matthieu          #+#    #+#             */
/*   Updated: 2021/10/20 03:22:45 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lst_size_exec(t_exec	*exec)
{
	t_exec	*temp;
	int		i;

	i = 0;
	temp = exec;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

int	check_built_in(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

void	exec_built_in(t_mini *mini, char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(mini, mini->exec->arg);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		ft_cd(mini, mini->exec->arg);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(mini, mini->exec->arg);
	if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(mini, mini->exec->arg);
	if (ft_strncmp(cmd, "export", 7) == 0)
		ft_export(mini, mini->exec->arg);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		ft_unset(mini, mini->exec->arg);
}

//

char	*define_command_path(char *path, char *command)
{
	char	*dest;
	int		i;
	int		j;

	dest = ft_calloc(ft_strlen(path) + ft_strlen(command) + 2, sizeof(char));
	i = 0;
	j = 0;
	if (dest == NULL)
		return (NULL);
	while (path[i])
	{
		dest[j] = path[i];
		j++;
		i++;
	}
	dest[j++] = '/';
	i = 0;
	while (command[i] != 0)
	{
		dest[j] = command[i];
		j++;
		i++;
	}
	return (dest);
}

char	**define_env_path(t_mini *mini)
{
	t_env	*temp;
	char	**dest;

	temp = get_env_var("PATH=", mini);
	if (temp == NULL || temp->value == NULL)
		return (NULL);
	dest = ft_split(&temp->value[5], ':');
	if (dest == NULL)
		return (NULL);
	return (dest);
}

int	fork_execve_define_path(t_mini *mini, t_exec *temp, char **args)
{
	int		i;
	char	*command_path;
	char	**path;

	i = 0;
	if (ft_strncmp(args[0], "/", 1) == 0
		|| ft_strncmp(args[0], "./", 2) == 0)
		execve(args[0], args, NULL);
	path = define_env_path(mini);
	if (path)
	{
		while (path[i])
		{
			command_path = define_command_path(path[i], args[0]);
			execve(command_path, args, NULL);
			i++;
			free(command_path);
		}
	}
	temp->return_value = 1;
	ft_free_tab(path);
	ft_free_tab(args);
	write(2, "Wrong command path\n", 20);
	return (1);
}

void	exec_single_case_function(t_mini *mini, t_exec *temp)
{
	int		fd[2];
	pid_t	pid;
	char	**args;

	if (pipe(fd) < 0)
	{
		mini->exec->return_value = 1;
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		mini->exec->return_value = 1;
		return ;
	}
	if (pid == 0)
	{
		args = ft_lstarg_in_tab(temp->arg);
		if (args == NULL)
		{
			close(fd[0]);
			close(fd[1]);
			mini->exec->return_value = 1;
			return ;
		}
		dup2(temp->infile_fd, 0);
		dup2(temp->outfile_fd, 1);
		close(temp->infile_fd);
		close(temp->outfile_fd);
		close(fd[0]);
		close(fd[1]);
		fork_execve_define_path(mini, temp, args);
	}
	close(temp->infile_fd);
	close(temp->outfile_fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &temp->return_value, 0);
}

int	execute_command(t_mini *mini)
{
	t_exec	*temp;

	temp = mini->exec;
	if (temp->arg && temp->arg->content)
	{
		if (check_built_in(temp->arg->content))
			exec_built_in(mini, temp->arg);
		else
			exec_single_case_function(mini, temp);
	}
	return (mini->exec->return_value);
}

void	setup_redir(t_mini *mini, t_exec *temp)
{
	while (temp && temp->redir)
	{
		if (ft_strncmp(mini->exec->redir->type, "<<",
				ft_strlen("<<")))
			ft_heredoc(mini, temp);
		else if (ft_strncmp(mini->exec->redir->type, "<", 2))
			ft_redir_infile(mini, temp);
		else if (ft_strncmp(mini->exec->redir->type, ">", 2))
			ft_redir_outfile(mini, temp, 0);
		else if (ft_strncmp(mini->exec->redir->type, ">>", 3))
			ft_redir_outfile(mini, temp, 1);
		temp->redir = temp->redir->next;
	}
}

void	single_command_case(t_mini *mini)
{
	t_exec	*temp;

	temp = mini->exec;
	if (mini->exec->redir)
		setup_redir(mini, temp);
	execute_command(mini);
	mini->last_return_value = mini->exec->return_value;
	return ;
}

void	ft_execution(t_mini *mini)
{
	int		command_number;

	mini->start_exec = mini->exec;
	command_number = ft_lst_size_exec(mini->exec);
	if (command_number == 0)
		return ;
	else if (command_number == 1)
		single_command_case(mini);
	else if (command_number > 1)
		multiple_command_case(mini, command_number);
	return ;
}
