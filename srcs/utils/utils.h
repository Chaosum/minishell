/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:45:47 by matthieu          #+#    #+#             */
/*   Updated: 2021/09/30 02:13:28 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

/* global_utils.c */

int		ft_tab_size(char **tab);
t_env	*get_env_var(char *get, t_mini	*mini);
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

/* ft_lstadd_back.c */
void	ft_lstadd_back_env(t_env **alst, t_env *new);

/* ft_lstadd_front.c */
void	ft_lstadd_front_env(t_env **alst, t_env *new);

/* ft_strlcat.c */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

/* first_memory_utils.c */
void	ft_free_tab(char **tab);

#endif