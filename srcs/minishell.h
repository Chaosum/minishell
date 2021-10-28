/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:39:38 by matthieu          #+#    #+#             */
/*   Updated: 2021/10/28 04:33:44 by mservage         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "minishell_struct.h"
# include "../libft/libft.h"
# include "./utils/utils.h"
# include "./exec/exec.h"
# include "./built_in/built_in.h"

/* minishell.c */

int		init_mini_struct_env(t_mini *mini, char **env);
void	init_mini_struct(t_mini *mini, char **env);
void	main_mini_temp(t_mini *mini);
int		parsing(t_mini *mini, char *line);
int		init_shell_level(t_mini *mini);
int		main(int ac, char **av, char **env);

#endif