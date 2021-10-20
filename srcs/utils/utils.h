/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:45:47 by matthieu          #+#    #+#             */
/*   Updated: 2021/10/18 17:42:59 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

/* global_utils.c */

int		ft_tab_size(char **tab);
t_env	*get_env_var(char *get, t_mini	*mini);
void	ft_free_tab(char **tab);
void	ft_add_env_var(char *value, t_mini *mini);

/* ft_lstadd_back.c */
void	ft_lstadd_back_env(t_env **alst, t_env *new);

/* ft_lstadd_front.c */
void	ft_lstadd_front_env(t_env **alst, t_env *new);

/* first_memory_utils.c */
void	ft_free_tab(char **tab);

#endif