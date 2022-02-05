/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:56:18 by mservage          #+#    #+#             */
/*   Updated: 2021/05/25 15:56:36 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_line	*ft_free_struck(t_line *lst, t_line *temp)
{
	t_line	*temp2;

	temp2 = lst;
	if (temp == lst && lst)
		lst = lst->next;
	else if (lst && temp)
	{
		while (temp2->next != temp)
			temp2 = temp2->next;
		temp2->next = temp->next;
	}
	free(temp->stock);
	free(temp);
	return (lst);
}
