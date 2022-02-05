/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:37:55 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/31 15:39:16 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_malloc_error(t_mini *mini, int ret_value)
{
	free_lexer(mini);
	printf("Malloc error during parsing\n");
	return (ret_value);
}

void	free_lexer(t_mini *mini)
{
	t_token	*temp;

	temp = mini->token;
	if (mini->token)
	{
		while (temp)
		{
			if (temp->arg)
				free(temp->arg);
			temp = temp->next;
			free(mini->token);
			mini->token = temp;
		}
		free(mini->token);
	}
}
