/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:43:23 by mservage          #+#    #+#             */
/*   Updated: 2021/05/25 12:44:37 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join_buf(char *src, char *buf)
{
	char	*dest;
	int		i;
	int		j;

	if (!(src) && !(buf))
		return (0);
	dest = ft_calloc((ft_strlen(src) + ft_strlen(buf) + 1), sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	if (src[0])
	{
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
	}
	if (buf[0])
	{
		while (buf[j])
			dest[i++] = buf[j++];
	}
	return (dest);
}

char	*ft_treatment_nl(char *join, char *dest, int i, t_line *lst)
{
	int	j;
	int	k;

	j = -1;
	k = 0;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (0);
	while (join[++j] != '\n' && (join[j]))
		dest[j] = join[j];
	dest[j] = 0;
	j++;
	free(lst->stock);
	lst->stock = malloc(sizeof(char) * (ft_strlen(&join[j]) + 1));
	if (!lst->stock)
		return (0);
	while (join[j])
	{
		lst->stock[k] = join[j++];
		k++;
	}
	lst->stock[k] = 0;
	if (join)
		free(join);
	return (dest);
}

char	*ft_treatment_nol(char *join, char *dest, int ret, t_line *lst)
{
	int	j;

	j = -1;
	if (ret == BUFFER_SIZE)
	{
		free(lst->stock);
		lst->stock = malloc(sizeof(char) * (ft_strlen(join) + 1));
		if (!lst->stock)
			return (0);
		while (join[++j])
			lst->stock[j] = join[j];
		lst->stock[j] = 0;
		dest = 0;
	}
	else if (ret < BUFFER_SIZE)
	{
		dest = malloc(sizeof(char) * ft_strlen(join) + 1);
		if (!dest)
			return (0);
		while (join[++j])
			dest[j] = join[j];
		dest[j] = 0;
	}
	free(join);
	return (dest);
}

char	*ft_treatment_zero(char *join, int i, char *dest)
{
	int	j;

	j = 0;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (0);
	while (join[j])
	{
		dest[j] = join[j];
		j++;
	}
	dest[j] = 0;
	if (join)
		free(join);
	return (dest);
}
