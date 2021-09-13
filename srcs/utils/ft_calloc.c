/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:27:54 by mservage          #+#    #+#             */
/*   Updated: 2021/09/10 14:06:03 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*ptr;

	i = 0;
	ptr = malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	while (i < (size * count))
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
