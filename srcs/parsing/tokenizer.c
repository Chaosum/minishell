/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:26:02 by rjeannot          #+#    #+#             */
/*   Updated: 2022/02/02 17:12:02 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_token(t_mini *mini, char *line, int start, int max)
{
	int			i;
	t_token		*token;

	i = 0;
	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (token_malloc_error(mini, 1));
	token->etat = -1;
	token->arg = ft_calloc(max - start + 1, sizeof(char));
	if (token->arg == NULL)
		return (token_malloc_error(mini, 1));
	while (start < max)
	{
		token->arg[i] = line[start];
		i++;
		start++;
	}
	ft_token_add_back(&mini->token, token);
	return (0);
}

int	tokenizer(char *line, t_mini *mini, t_token_var *v)
{
	if (line[v->i] == '$' && (line[v->i + 1] == 34 || line[v->i + 1] == 39))
		v->prev = v->i++ + 1;
	while (line[v->i])
	{
		if (line[v->i] == 34 && v->single_quote == 0)
			v->double_quote = !v->double_quote;
		else if (line[v->i] == 39 && v->double_quote == 0)
			v->single_quote = !v->single_quote;
		if (is_redir(v->double_quote, v->single_quote, v->i, line))
		{
			if (create_redir_token(mini, line, &v->i))
				return (1);
			break ;
		}
		else if (is_token(v->double_quote, v->single_quote, v->i, line))
		{
			if (create_token(mini, line, v->prev, v->i + 1))
				return (1);
			v->i++;
			break ;
		}
		v->i++;
	}
	return (0);
}

int	start_token(char *line, t_mini *mini)
{
	t_token_var	var;

	init_t_token(&var);
	while (line[var.i])
	{
		skip_isspace(line, &var.i, &var.prev);
		if (tokenizer(line, mini, &var))
			break ;
		skip_isspace(line, &var.i, &var.prev);
	}
	if (var.double_quote || var.single_quote)
	{
		printf("Double quotes error\n");
		return (1);
	}
	return (0);
}
