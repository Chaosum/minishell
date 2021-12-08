/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:45:12 by matthieu          #+#    #+#             */
/*   Updated: 2021/12/08 11:59:23 by matthieu         ###   ########.fr       */
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
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		ft_cd(mini, mini->exec->arg);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(mini, mini->exec->arg);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(mini, mini->exec->arg);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ft_export(mini, mini->exec->arg);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ft_unset(mini, mini->exec->arg);
}

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
	else
	{
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
	}
	temp->return_value = 1;
	ft_free_tab(path);
	ft_free_tab(args);
	write(2, "Wrong command path\n", 20);
	return (1);
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

void	ft_free_env(t_mini *mini)
{
	t_env *temp;

	while (mini->env)
	{
		free(mini->env->value);
		temp = mini->env->next;
		free(mini->env);
		mini->env = temp;
	}
}

void	free_lst_exec(t_mini *mini)
{
	t_exec	*temp;
	t_arg	*temp2;
	t_redir	*temp3;

	while (mini->exec)
	{
		temp = mini->exec->next;
		temp2 = mini->exec->arg;
		temp3 = mini->exec->redir;
		while (temp2)
		{
			free(temp2->content);
			temp2 = temp2->next;
			free(mini->exec->arg);
			mini->exec->arg = temp2;
		}
		while (temp3)
		{
			free(temp3->file);
			free(temp3->type);
			temp3 = temp3->next;
			free(mini->exec->redir);
			mini->exec->redir = temp3;
		}
		if (mini->exec->heredoc)
			free(mini->exec->heredoc);
		if (mini->exec->infile_fd != 0 && mini->exec->infile_fd != 1)
			close(mini->exec->infile_fd);
		if (mini->exec->outfile_fd != 1 && mini->exec->outfile_fd != 0)
			close(mini->exec->outfile_fd);
		free(mini->exec);
		mini->exec = temp;
	}
}

void	ft_execution(t_mini *mini)
{
	int	command_number;

	command_number = ft_lst_size_exec(mini->exec);
	if (command_number == 0)
		return ;
	else if (command_number == 1)
		single_command_case(mini);
	else if (command_number > 1)
		multiple_command_case(mini, command_number);
	free_lst_exec(mini);
	return ;
}
