/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:45:47 by matthieu          #+#    #+#             */
/*   Updated: 2021/09/10 14:06:59 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

/* global_utils.c */

int		ft_tab_size(char **tab);
char	*get_env_var(char *get, char **env);
void	ft_free_all(t_malloc malloced);
int		ft_error_exit(char *msg, t_mini *mini);
void	ft_free_tab(char **tab);

/* ft_atoi.c */

int		ft_atoi(const char *str);

/* ft_calloc.c */

void	*ft_calloc(size_t count, size_t size);

/* ft_itoa.c */
char	*ft_itoa(int n);

/* ft_strdup.c */
char	*ft_strdup(const char *s1);

/* ft_strjoin.c */
char	*ft_strjoin(char const *s1, char const *s2);

/* ft_strlen.c */
int		ft_strlen(const char *s);

/* ft_strncmp.c */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif