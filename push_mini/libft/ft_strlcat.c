/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeannot <rjeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:09:29 by mservage          #+#    #+#             */
/*   Updated: 2021/04/29 14:53:12 by rjeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (dst[j])
		j++;
	while (src[i])
		i++;
	k = i + j;
	if (j >= dstsize)
		return (i + dstsize);
	i = 0;
	while ((i < dstsize - j - 1) && src[i])
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = 0;
	i = 0;
	return (k);
}
