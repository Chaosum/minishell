/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:39:38 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/25 13:46:35 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "minishell_struct.h"
# include "../libft/libft.h"
# include "./utils/utils.h"
# include "./exec/exec.h"
# include "./built_in/built_in.h"
# include "./parsing/parsing.h"

/* minishell.c */

int		init_mini_struct_env(t_mini *mini, char **env);
void	init_mini_struct(t_mini *mini, char **env);
void	main_mini_temp(t_mini *mini);
int		init_shell_level(t_mini *mini);
void	sigint_handler(int signum);
int		main(int ac, char **av, char **env);

#endif