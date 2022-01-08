/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:26:02 by rjeannot          #+#    #+#             */
/*   Updated: 2022/01/06 13:59:42 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_mini *mini)
{
}

int	create_redir_token(t_mini *mini, char *line, int *i)
{
	t_token		*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		free_token(mini); /* a free correctement */
	if (line[*i] == '|')
	{
		token->arg = ft_strdup("|");
		if (token->arg == NULL)
			free_token(mini);
		token->etat = is_pipe;
		*i = *i + 1;
	}
	else if (line[*i] == '>')
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
	}
	else if (line[*i] == '<')
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
			token->etat = redirection_out;
			*i = *i + 1;
		}
	}
	ft_token_add_back(&mini->token, token);
	return (0);
}

int	create_token(t_mini *mini, char *line, int start, int max)
{
	int			i;
	t_token		*token;

	i = 0;
	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
	{
		free_token(mini); /* a free correctement */
		return (1);
	}
	token->etat = -1;
	token->arg = ft_calloc(max - start + 1, sizeof(char));
	if (token->arg == NULL)
	{
		free_token(mini); /* a free correctement */
		return (1);
	}
	while (start < max)
	{
		token->arg[i] = line[start];
		i++;
		start++;
	}
	ft_token_add_back(&mini->token, token);
	return (0);
}

int	start_token(char *line, t_mini *mini)
{
	int		i;
	int		prev;
	int		single_quote;
	int		double_quote;

	i = 0;
	prev = 0;
	single_quote = 0;
	double_quote = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '|' && double_quote == 0 && single_quote == 0)
		{
			printf("Parse error near \"|\"\n");
			return (1);
		}
		while (line[i])
		{
			if (line[i] == 34 && single_quote == 0)
				double_quote = !double_quote;
			else if (line[i] == 39 && double_quote == 0)
				single_quote = !single_quote;
			if ((line[i] == '|' || line[i] == '>' || line[i] == '<')
				&& double_quote == 0
				&& single_quote == 0)
			{
				if (create_redir_token(mini, line, &i))
					return (1);
				break ;
			}
			else if ((line[i + 1] == 0
					|| ((ft_isspace(line[i + 1]) && double_quote == 0
							&& single_quote == 0)
						|| (line[i + 1] == '|' && double_quote == 0
							&& single_quote == 0)
						|| (line[i + 1] == '>' && double_quote == 0
							&& single_quote == 0)
						|| (line[i + 1] == '<' && double_quote == 0
							&& single_quote == 0)
						&& i != prev)))
			{
				if (create_token(mini, line, prev, i + 1))
					return (1);
				i++;
				break ;
			}
			i++;
		}
		while (ft_isspace(line[i]))
			i++;
		prev = i;
	}
	if (double_quote || single_quote)
		printf("Double quotes error\n");
	return (0);
}
