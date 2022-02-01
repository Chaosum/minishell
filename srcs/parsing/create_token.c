/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:19:07 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/01 01:27:10 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_pipe_case(t_mini *mini, t_token *token, int *i)
{
	token->arg = ft_strdup("|");
	if (token->arg == NULL)
		return (token_malloc_error(mini, 1));
	token->etat = is_pipe;
	*i = *i + 1;
	return (0);
}

int	create_redir_out_case(t_token *token, char *line, int *i)
{
	if (line[*i + 1] == '>')
	{
		if (line[*i + 2] == '>')
		{
			printf("Syntax error near >\n");
			return (1);
		}
		token->arg = ft_strdup(">>");
		token->etat = redirection_out_append;
		*i = *i + 2;
	}
	else if (line[*i + 1] == '<' || line[*i + 1] == '|')
	{
		printf("Syntax error near >\n");
		return (1);
	}
	else
	{
		token->arg = ft_strdup(">");
		token->etat = redirection_out;
		*i = *i + 1;
	}
	return (0);
}

int	create_redir_in_case(t_token *token, char *line, int *i)
{
	if (line[*i + 1] == '<')
	{
		if (line[*i + 2] == '>')
		{
			printf("Syntax error near >\n");
			return (1);
		}
		token->arg = ft_strdup("<<");
		token->etat = heredoc;
		*i = *i + 2;
	}
	else if (line[*i + 1] == '>' || line[*i + 1] == '|')
	{
		printf("Syntax error near <\n");
		return (1);
	}
	else
	{
		token->arg = ft_strdup("<");
		token->etat = redirection_in;
		*i = *i + 1;
	}
	return (0);
}

int	create_redir_token(t_mini *mini, char *line, int *i)
{
	t_token		*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (token_malloc_error(mini, 1));
	if (line[*i] == '|')
	{
		if (create_pipe_case(mini, token, i))
			return (1);
	}
	else if (line[*i] == '>')
	{
		if (create_redir_out_case(token, line, i))
			return (1);
	}
	else if (line[*i] == '<')
	{
		if (create_redir_in_case(token, line, i))
			return (1);
	}
	ft_token_add_back(&mini->token, token);
	return (0);
}
