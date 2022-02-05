/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:42:54 by mservage          #+#    #+#             */
/*   Updated: 2021/05/25 15:56:56 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_line	*ft_foundfd(int fd, t_line *list)
{
	t_line	*temp;

	temp = list;
	if (fd < 0)
		return (0);
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	return (0);
}

t_line	*new_fd(int fd, t_line *list)
{
	t_line	*temp[2];

	temp[1] = list;
	temp[0] = NULL;
	while (temp[1])
	{
		if (temp[1]->fd == fd)
			return (list);
		temp[1] = temp[1]->next;
	}
	temp[0] = malloc(sizeof(t_line));
	if (!(temp[0]))
		return (0);
	temp[0]->stock = malloc(sizeof(char));
	if (!(temp[0]->stock))
	{
		free(temp[0]);
		return (0);
	}
	temp[0]->stock[0] = 0;
	temp[0]->fd = fd;
	temp[0]->next = list;
	list = temp[0];
	return (temp[0]);
}

int	ft_treatment(char *join, t_line *lst, char **line, int i[2])
{
	if (join[i[1]] == '\n')
	{
		*line = ft_treatment_nl(join, *line, i[1], lst);
		if (*line)
			return (1);
	}
	if (i[0] == 0)
	{
		*line = ft_treatment_zero(join, i[1], *line);
		if (*line)
			return (0);
	}
	if ((join[i[1]] != '\n'))
	{
		*line = ft_treatment_nol(join, *line, i[0], lst);
		if (*line)
			return (0);
	}
	return (-1);
}

int	ft_reading(int fd, char *buf, t_line *lst, char **line)
{
	int		i[2];
	int		return_val;
	char	*join;

	i[1] = 0;
	i[0] = read(fd, buf, BUFFER_SIZE);
	join = "";
	while (i[0] >= 0 && BUFFER_SIZE > 0)
	{
		buf[i[0]] = 0;
		join = ft_join_buf(lst->stock, buf);
		while ((join[i[1]] != '\n') && (join[i[1]] != 0))
			i[1]++;
		return_val = ft_treatment(join, lst, line, i);
		if (return_val == 0)
			return (0);
		else if (return_val == 1)
			return (1);
		i[0] = read(fd, buf, BUFFER_SIZE);
	}
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	static t_line		*lst = NULL;
	char				*buf;
	int					result;

	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
	{
		if (lst)
			lst = ft_free_struck(lst, NULL);
		return (-1);
	}
	lst = new_fd(fd, lst);
	if (fd < 0 || !line || (!(lst)) || (read(fd, buf, 0) < 0))
	{
		free(buf);
		if (lst)
			lst = ft_free_struck(lst, ft_foundfd(fd, lst));
		return (-1);
	}
	result = ft_reading(fd, buf, ft_foundfd(fd, lst), line);
	if (result == 0 || result == -1)
		lst = ft_free_struck(lst, ft_foundfd(fd, lst));
	free(buf);
	return (result);
}
