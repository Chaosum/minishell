/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:39:38 by matthieu          #+#    #+#             */
/*   Updated: 2021/09/10 13:54:21 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell_struct.h"
# include "./utils/utils.h"
# include "./exec/exec.h"

/* minishell.c */

void	init_mini_struct_malloced(t_mini *mini);
void	init_mini_struct_env(t_mini *mini, char **env);
void	init_mini_struct(t_mini *mini, char **env);
void	ft_add_env_var(t_mini *mini, char *env);
int		parsing(char *line, char **env);
void	init_shell_level(t_mini *mini);
int		main(int ac, char **av, char **env);

#endif