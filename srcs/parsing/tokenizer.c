/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:26:02 by rjeannot          #+#    #+#             */
/*   Updated: 2021/12/01 04:28:30 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_mini *mini)
{
}

void	create_redir_token(mini, line, prev, i)
{
}

void	create_token(t_mini *mini, char *line, int start, int max)
{
	int			i;
	t_token		*token;

	i = 0;
	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		free_token(mini); /* a free correctement */
	token->arg = ft_calloc(max - start + 1, sizeof(char));
	if (token->arg == NULL)
		free_token(mini); /* a free correctement */
	while (start < max)
	{
		token->arg[i] = line[start];
		i++;
		start++;
	}
	ft_token_add_back(&mini->token, token);
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
				create_redir_token(mini, line, prev, i);
				i++;
				break ;
			}
			else if ((line[i + 1] == 0 || ft_isspace(line[i])) && i != prev
				|| (line[i + 1] == '|' && double_quote == 0
					&& single_quote == 0))
			{
				create_token(mini, line, prev, i);
				i++;
				break ;
			}
			i++;
		}
		prev = i;
	}
	if (double_quote || single_quote)
		printf("Double quotes error\n");
	return (0);
}
