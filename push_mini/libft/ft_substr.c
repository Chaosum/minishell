/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:33:34 by mservage          #+#    #+#             */
/*   Updated: 2021/05/16 10:49:18 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_smaller(int a, int b)
{
	if (a >= b)
		return (b);
	return (a);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s))
	{
		dest = malloc(sizeof(char));
		if (dest == NULL)
			return (NULL);
		*dest = 0;
		return (dest);
	}
	dest = malloc(sizeof(char) * (ft_smaller(ft_strlen(s), len) + 1));
	if (dest == NULL)
		return (NULL);
	if (s)
	{
		i = -1;
		while (++i < len && s[start + i])
			dest[i] = s[start + i];
	}
	dest[i] = 0;
	return (dest);
}
