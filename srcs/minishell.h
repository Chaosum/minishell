/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:39:38 by matthieu          #+#    #+#             */
/*   Updated: 2021/09/30 02:15:22 by mservage         ###   ########.fr       */
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
# include "minishell_struct.h"
# include "./utils/utils.h"
# include "./exec/exec.h"
# include "./built_in/built_in.h"

/* minishell.c */

void	init_mini_struct_malloced(t_mini *mini);
void	init_mini_struct_env(t_mini *mini, char **env);
void	init_mini_struct(t_mini *mini, char **env);
void	ft_add_env_var(char *value, t_mini *mini);
int		parsing(t_mini *mini, char *line);
void	init_shell_level(t_mini *mini);
void	change_env_var_value(t_mini *mini, t_env *var, char *content);
int		main(int ac, char **av, char **env);

#endif