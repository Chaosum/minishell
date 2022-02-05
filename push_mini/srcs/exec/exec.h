/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:45:31 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/04 15:27:11 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

/* built_in_exec.c */
int		check_built_in(char *cmd);
void	exec_built_in(t_mini *mini, char *cmd);

/* exec_pipe.c */
int		verif_pipe_tab(int command_number, int *pipe_fd);
void	pipe_execve_fork(t_exec *temp, int *pipe_fd, int i, int command_number);
int		pid_fork_error(pid_t *pid, int i, int *pipe_fd, int command_number);
int		execute_pipe_command(t_mini *mini, t_exec *temp);
void	ft_wait_fork(t_mini *mini, pid_t *pid, int cmd_nbr);

/* exec_single_command.c */
void	exec_single_case_function_fork(t_mini *mini, t_exec *temp,
			char **args, int fd[2]);
void	exec_heredoc_write(t_exec *temp, int fd[2]);
void	close_all_fd(int ffd, int sfd, t_exec *temp);
void	exec_single_case_function(t_mini *mini, t_exec *temp, char **args);
int		execute_single_command(t_mini *mini);

/* exec_utils.c */
int		init_pipe_tab(int *pipe_fd, int command_number, pid_t *pid);
char	**define_env_path(t_mini *mini);
int		t_arg_number_content(t_arg *temp);
char	**ft_lstarg_in_tab(t_arg *prms);
int		ft_lst_size_exec(t_exec	*exec);

/* exec.c */
void	multiple_command_case(t_mini *mini, int command_number, int i);
void	single_command_case(t_mini *mini);
void	ft_execution(t_mini *mini);

/* execution.c */
char	*define_command_path(char *path, char *command);
void	write_command_error(char **args);
void	free_fork_execve(t_mini *mini, char **path, char **args);
int		fork_execve_define_path(t_mini *mini, char **args);

/* free_exec.c */
void	ft_free_pipe_tab(int *pipe_fd, int command_number, int mode);
void	free_lst_arg(t_mini *mini, t_arg *temp2);
void	free_lst_redir(t_mini *mini, t_redir *temp3);
void	free_lst_exec(t_mini *mini);

/* heredoc.c */
void	heredoc_pipe(t_redir *temp_redir, int fd[2]);
void	heredoc_end(t_mini *mini, t_exec *temp_exec, int fd[2]);
void	heredoc_fork(t_mini *mini, int fd[2], t_redir *temp_redir);
int		ft_heredoc(t_mini *mini, t_exec *temp_exec, t_redir *temp_redir);

/* redir_infile.c */
int		redir_check_opening_error(t_redir *temp_redir);
int		ft_redir_infile(t_exec *exec, t_redir *temp_redir);
int		ft_redir_outfile(t_exec *exec, t_redir *temp_redir, int append);

/* redir.c */
int	setup_redir(t_mini *mini, t_exec *temp);

#endif