/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:45:31 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/27 18:52:55 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

/* exec_pipe.c */

void	ft_free_pipe_tab(int *pipe_fd, int command_number);
int		init_pipe_tab(int *pipe_fd, int command_number, pid_t *pid);
int		execute_pipe_command(t_mini *mini, t_exec *temp);
void	multiple_command_case(t_mini *mini, int command_number);

/* exec_single_case_function.c */

void	sigint_handler_cat(int signum);
void	sigint_handler_quit(int signum);
void	exec_single_case_function(t_mini *mini, t_exec *temp);
int		execute_single_command(t_mini *mini);
void	single_command_case(t_mini *mini);

/* exec.c */
int		ft_lst_size_exec(t_exec	*exec);
int		check_built_in(char *cmd);
void	exec_built_in(t_mini *mini, char *cmd);
char	*define_command_path(char *path, char *command);
char	**define_env_path(t_mini *mini);
int		fork_execve_define_path(t_mini *mini, t_exec *temp, char **args);
void	setup_redir(t_mini *mini, t_exec *temp);
void	ft_free_env(t_mini *mini);
void	free_lst_exec(t_mini *mini);
void	ft_execution(t_mini *mini);

/* heredoc.c */

void	ft_heredoc(t_mini *mini, t_exec *temp_exec, t_redir *temp_redir);

/* redir_infile.c */

int		redir_check_opening_error(t_redir *temp_redir);
void	ft_redir_infile(t_exec *exec, t_redir *temp_redir);
void	ft_redir_outfile(t_exec *exec, t_redir *temp_redir, int append);

#endif