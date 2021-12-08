/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:25:46 by rjeannot          #+#    #+#             */
/*   Updated: 2021/12/08 11:13:36 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(t_mini *mini, char *line)
{
	start_token(line, mini);
	lexer(mini);
	ft_execution(mini);
}
