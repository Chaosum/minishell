/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:09:29 by mservage          #+#    #+#             */
/*   Updated: 2021/09/24 14:57:43 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
