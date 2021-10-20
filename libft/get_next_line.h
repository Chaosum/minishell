/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:43:03 by mservage          #+#    #+#             */
/*   Updated: 2021/05/24 17:24:36 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# define BUFFER_SIZE 1

typedef struct s_line
{
	int				fd;
	char			*stock;
	struct s_line	*next;
}				t_line;
char				*ft_join_buf(char *src, char *buf);
t_line				*new_fd(int fd, t_line *list);
char				*ft_treatment_nl(char *join, char *dest,
						int i, t_line *lst);
char				*ft_treatment_nol(char *join, char *dest,
						int ret, t_line *lst);
char				*ft_treatment_zero(char *join, int i, char *dest);
int					get_next_line(int fd, char **line);
int					ft_reading(int fd, char *buf, t_line *lst, char **line);
t_line				*ft_foundfd(int fd, t_line *list);
t_line				*ft_free_struck(t_line *lst, t_line *temp);

#endif
