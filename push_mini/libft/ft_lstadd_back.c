/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:15:02 by mservage          #+#    #+#             */
/*   Updated: 2020/12/02 15:19:49 by mservage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (*alst == 0)
	{
		*alst = new;
		return ;
	}
	temp = *alst;
	while (temp)
	{
		if (temp->next == 0)
		{
			temp->next = new;
			return ;
		}
		temp = temp->next;
	}
	return ;
}
