/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:09:44 by rjeannot          #+#    #+#             */
/*   Updated: 2022/02/03 14:34:54 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_token(t_mini *mini)
{
	t_token	*temp;

	temp = mini->token;
	while (temp)
	{
		if (temp->etat == 0 || temp->etat == 1 || temp->etat == 2
			|| temp->etat == 3)
		{
			check_token_redir(temp);
		}
		else if (temp->etat != is_pipe)
			temp->etat = litteral;
		else if (temp->etat == is_pipe)
			if (temp->next == NULL || temp->next->etat == is_pipe)
				return (1);
		temp = temp->next;
	}
	return (0);
}

void	add_char_dest(t_lexer_var *v, t_token *temp)
{
	int		i;
	char	*dest;

	i = 0;
	dest = ft_calloc(ft_strlen(v->dest) + 2, sizeof(char));
	while (v->dest[i])
	{
		dest[i] = v->dest[i];
		i++;
	}
	dest[i] = temp->arg[v->i];
	free(v->dest);
	v->dest = dest;
}

int	replace_braces(t_token *temp, t_mini *mini, t_lexer_var	v)
{
	init_var_lexer(&v);
	v.dest = ft_calloc(ft_strlen(temp->arg) + 1, sizeof(char));
	if (v.dest == NULL)
		return (printf("malloc error\n"));
	while (temp->arg[v.i])
	{
		if (temp->arg[v.i] == 34 && temp->single_quote == 0)
			temp->double_quote = !temp->double_quote;
		else if (temp->arg[v.i] == 39 && temp->double_quote == 0)
			temp->single_quote = !temp->single_quote;
		else if (temp->single_quote == 0 && temp->arg[v.i] == '$'
			&& ft_strlen(temp->arg) > 1)
		{
			v.i++;
			v.replace_temp = replace_by_env(mini, temp, &v.i, &v.j);
			v.dest = ft_strjoin(v.dest, v.replace_temp);
			v.i--;
		}
		else
			add_char_dest(&v, temp);
		v.i++;
	}
	free(temp->arg);
	temp->arg = v.dest;
	return (0);
}

int	purge_token(t_mini *mini)
{
	t_token		*temp;
	t_lexer_var	v;

	temp = mini->token;
	while (temp)
	{
		init_var_lexer(&v);
		if (replace_braces(temp, mini, v))
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	lexer(t_mini *mini)
{
	t_token	*temp;
	int		ret;

	temp = mini->token;
	ret = 0;
	if (temp)
	{
		if (purge_token(mini) == 0)
		{
			if (parse_token(mini) == 0)
				ret = lexer_exec(mini);
		}
		else
		{
			printf("Parse error near |\n");
			ret = 1;
		}
		free_lexer(mini);
	}
	return (ret);
}
