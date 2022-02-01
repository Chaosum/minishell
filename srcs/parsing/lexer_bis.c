/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:02:10 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/01 02:21:54 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	creating_redir(t_token *temp)
{
	if (temp == NULL || ft_strncmp(temp->arg, "|", 2) == 0)
	{
		if (temp)
			printf("parse error near %s\n", temp->arg);
		else
			printf("parse error near newline\n");
		return (1);
	}
	return (0);
}

void	lexer_exec_treatment(t_mini *mini, t_exec *temp_exec, t_token *temp)
{
	while (temp)
	{
		if (temp->etat < 4)
		{
			create_redir(temp_exec, temp);
			temp = temp->next;
			if (temp)
				temp = temp->next;
			else if (creating_redir(temp))
				return ;
		}
		else if (temp->etat == is_pipe)
		{
			create_exec(mini);
			temp_exec = temp_exec->next;
			temp = temp->next;
		}
		else
		{
			create_arg(temp_exec, temp);
			temp = temp->next;
		}
	}
}

int	lexer_exec(t_mini *mini)
{
	t_token	*temp;
	t_exec	*temp_exec;

	temp = mini->token;
	if (temp)
	{
		create_exec(mini);
		temp_exec = mini->exec;
	}
	if (mini->exec == NULL)
	{
		printf("Malloc error\n");
		return (1);
	}
	lexer_exec_treatment(mini, temp_exec, temp);
	return (0);
}
