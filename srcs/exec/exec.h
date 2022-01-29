/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:45:31 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/29 16:44:07 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

/* execution.c */
char	*define_command_path(char *path, char *command);
int		fork_execve_define_path(t_mini *mini, t_exec *temp, char **args);


/* heredoc.c */
void	heredoc_pipe(t_redir *temp_redir, int fd[2]);
void	free_mini_heredoc(t_mini *mini);
void	heredoc_fork(t_mini *mini, int fd[2], t_redir *temp_redir);
void	ft_heredoc(t_mini *mini, t_exec *temp_exec, t_redir *temp_redir);

/* redir_infile.c */
int		redir_check_opening_error(t_redir *temp_redir);
void	ft_redir_infile(t_exec *exec, t_redir *temp_redir);
void	ft_redir_outfile(t_exec *exec, t_redir *temp_redir, int append);

/* free_exec.c */
void	ft_free_pipe_tab(int *pipe_fd, int command_number);
void	free_lst_exec(t_mini *mini);

/* built_in_exec.c */
int		check_built_in(char *cmd);
void	exec_built_in(t_mini *mini, char *cmd);

/* exec_utils.c */
int		init_pipe_tab(int *pipe_fd, int command_number, pid_t *pid);
char	**define_env_path(t_mini *mini);
int		t_arg_number_content(t_arg *temp);
char	**ft_lstarg_in_tab(t_arg *prms);
int		ft_lst_size_exec(t_exec	*exec);


/* exec_pipe.c */
int		execute_pipe_command(t_mini *mini, t_exec *temp);
void	ft_wait_fork(pid_t *pid, int cmd_nbr);

/* exec_single_case_function.c */
void	exec_single_case_function(t_mini *mini, t_exec *temp);
int		execute_single_command(t_mini *mini);

/* redir.c */
void	setup_redir(t_mini *mini, t_exec *temp);

/* exec.c */
void	multiple_command_case(t_mini *mini, int command_number);
void	single_command_case(t_mini *mini);
void	ft_execution(t_mini *mini);

#endif