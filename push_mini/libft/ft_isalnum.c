/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:29:49 by mservage          #+#    #+#             */
/*   Updated: 2021/10/18 18:13:58 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (((c >= '0') && (c <= '9'))
		|| ((c >= 'a') && (c <= 'z'))
		|| ((c >= 'A') && (c <= 'Z')))
		return (1);
	return (0);
}
