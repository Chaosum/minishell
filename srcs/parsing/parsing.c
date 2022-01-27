/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:25:46 by rjeannot          #+#    #+#             */
/*   Updated: 2022/01/27 13:56:23 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(t_mini *mini, char *line)
{
	if (start_token(line, mini) == 0)
	{
		if (lexer(mini) == 0)
			ft_execution(mini);
	}
}
