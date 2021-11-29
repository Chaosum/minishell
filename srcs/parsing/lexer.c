/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:09:44 by rjeannot          #+#    #+#             */
/*   Updated: 2021/11/26 10:35:40 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*lexer_litteral(t_token *token)
{
	char		*str;
	t_token		*temp;
	int			i;

	i = 0;
	temp = token;
	temp->single_quote = 0;
	temp->double_quote = 0;
	while (temp->arg[i])
	{
		if (temp->arg[i] == 34)
			temp->double_quote = !temp->double_quote;
		else if (temp->arg[i] == 39)
			temp->single_quote = !temp->single_quote;
		if (temp->arg[i] == '$' && !temp->double_quote)
		{
		}
	}
}

void	fill_redir(t_mini *mini)
{
	t_token	*temp;
	t_redir	redir;

	temp = mini->token;
	redir.type = temp->arg;
	ft_lstarg_back();
}

void	check_arg(t_mini *mini)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = mini->token;
	while (temp->arg[i])
	{
		if (temp->etat == redirection_in
			|| temp-> etat == redirection_out)
			fill_redir(mini);
		i++;
	}
}

void	lexer(t_mini *mini)
{
	while (mini->token)
	{
		check_token(mini);
		mini->token->next;
	}
}
