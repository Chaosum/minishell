/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:06:14 by mservage          #+#    #+#             */
/*   Updated: 2020/12/03 17:54:47 by mservage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	b;

	b = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)src)[i] == b)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			return (dest + ++i);
		}
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (NULL);
}
