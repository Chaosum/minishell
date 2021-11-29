/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:26:02 by rjeannot          #+#    #+#             */
/*   Updated: 2021/11/26 13:03:45 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_token(void)
{
	t_token	*temp;

	temp = ft_calloc(1, sizeof(t_token));
	if (temp == NULL)
		return (NULL);
	temp->single_quote = 0;
	temp->double_quote = 0;
	return (temp);
}

void	create_token(t_mini *mini, char *line, int start, int max)
{
	int			i;
	t_token		*token;

	i = 0;
	token = init_token();
	token->arg = ft_calloc(max - start, sizeof(char));
	if (token->arg == NULL)
		return (1);
	while (start < max)
	{
		token->arg[i] = line[start];
		i++;
		start++;
	}
	ft_token_add_back(mini->token, token);
}

int	is_redir_outfile(char *line, int i, int *prev)
{
	if (line[i] == '<')
	{
		while (ft_isspace(line[i]) && line[i])
			i++;
		if (line[i + 1] == '<')
		{
			while (ft_isspace(line[i]))
				i++;
			if (line[i] == '<' || line[i] == '|'
				|| line[i] == '>' || line[i] == 0)
				return (1);
		}
		else if (line[i] == '<' || line[i] == '|'
			|| line[i] == '>' || line[i] == 0)
			return (1);
	}
	return (0);
}

int	is_redir_infile(char *line, int i, int *prev)
{
	int	temp_i;

	temp_i = i;
	if (line[i] == '>')
	{
		i++;
		while (ft_isspace(line[i]) && line[i])
			i++;
		if (line[temp_i + 1] == '>')
		{
			while (ft_isspace(line[i]) && line[i])
				i++;
			if (line[i] == '>' || line[i] == '|'
				|| line[i] == '<' || line[i] == 0)
				return (1);
		}
		else if (line[i] == '<' || line[i] == '|' || line[i] == '>')
			return (1);
	}
	return (0);
}

int	check_redir(t_mini *mini, char *line, int *prev, int i)
{
	if (is_redir_infile)
	{
	}
	return (0);
}

int start_token(char *line, t_mini *mini)
{
	int		i;
	int		prev;
	int		single_quote;
	int		double_quote;

	i = 0;
	prev = 0;
	single_quote = 0;
	double_quote = 0;
	while (ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		if (line[i] == 34 && single_quote == 0)
			double_quote = !double_quote;
		else if (line[i] == 39 && double_quote == 0)
			single_quote = !single_quote;
		if (ft_isspace(line[i]) && !double_quote && !single_quote)
		{
			create_token(mini, line, prev, i);
			while (ft_isspace(line[i]) && line[i])
				i++;
			prev = i;
		}
		else if (!single_quote && !double_quote)
		{
		}
		if (check_redir(mini, line, &prev, i))
		{
		}
		else if (is_redir_outfile(line, i, &prev)
			|| (is_redir_infile(line, i, &prev))
			&& !single_quote && !double_quote)
		{
			printf("ERROR_REDIR\n");
		}
		else
			i++;
	}
	if (prev != i)
		create_token(mini, line, prev, i);
	return (0);
}
