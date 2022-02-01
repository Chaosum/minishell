/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:06:58 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/01 01:43:53 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_var_lexer(t_lexer_var *var)
{
	var->dest = NULL;
	var->replace_temp = NULL;
	var->i = 0;
	var->j = 0;
}

int	is_token(int double_quote, int single_quote, int i, char *line)
{
	if (line[i + 1] == 0
		|| (ft_isspace(line[i + 1]) && double_quote == 0
			&& single_quote == 0)
		|| (line[i + 1] == '|' && double_quote == 0
			&& single_quote == 0)
		|| (line[i + 1] == '>' && double_quote == 0
			&& single_quote == 0)
		|| (line[i + 1] == '<' && double_quote == 0
			&& single_quote == 0))
		return (1);
	return (0);
}

void	skip_isspace(char *line, int *i, int *prev)
{
	while (ft_isspace(line[*i]))
		*i = *i + 1;
	*prev = *i;
}

int	is_redir(int double_quote, int single_quote, int i, char *line)
{
	if ((line[i] == '|' || line[i] == '>' || line[i] == '<')
		&& double_quote == 0
		&& single_quote == 0)
		return (1);
	return (0);
}

void	init_t_token(t_token_var *var)
{
	var->i = 0;
	var->prev = 0;
	var->single_quote = 0;
	var->double_quote = 0;
}
