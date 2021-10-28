/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:26:27 by mservage          #+#    #+#             */
/*   Updated: 2021/10/28 01:28:40 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../minishell.h"

/* cd.c */

int		t_arg_number_content(t_arg *temp);
char	**ft_lstarg_in_tab(t_arg *prms);
void	change_oldpwd(t_mini *mini, char *old_path);
void	change_pwd(t_mini *mini, char *path);
void	cd_no_arg(t_mini *mini);
void	ft_cd_path(t_mini *mini, char **args);
void	ft_cd(t_mini *mini, t_arg *prms);

/* echo.c */

void	echo_print(char **args, t_mini *mini);
int		check_echo_arg(char **av);
void	ft_echo(t_mini *mini, t_arg *prms);

/* env.c */
void	ft_env(t_mini *mini, t_arg *prms);
void	ft_print_env(t_env *env, t_mini *mini);

/* exit.c */
void	ft_exit_free_all(t_mini *mini, int exit_value);
void	ft_exit(t_mini *mini, t_arg *prms);

/* export.c */
int		check_if_valid_var(char *arg, int *error);
int		check_already_exist(t_mini *mini, char *args);
int		modify_existing_var(t_mini *mini, char *args);
void	ft_export(t_mini *mini, t_arg *prms);

/* pwd.c */

void	ft_pwd(t_mini *mini, t_arg *prms);

/* unset.c */

void	delete_var(t_mini *mini, t_env *temp, t_env *previous);
void	ft_remove_env(t_mini *mini, char *arg);
int		check_if_correct_unset(char *args);
void	ft_unset(t_mini *mini, t_arg *prms);

#endif