/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:09:44 by rjeannot          #+#    #+#             */
/*   Updated: 2021/11/29 19:00:33 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env)
{
	int	i;

	i = 0;
	while (env->value[i] != '=' && env->value[i])
		i++;
	return (&env->value[i]);
}

char	*replace_by_env(t_mini *mini, t_token *temp, int *i, int *j)
{
	char	env[2048];
	t_env	*temp_env;
	int		k;

	k = 0;
	while (temp->arg[*i] && ft_isalnum(temp->arg[*i]) && k < 2048)
	{
		env[k] = temp->arg[*i];
		*i = *i + 1;
		k++;
	}
	env[k] = 0;
	temp_env = get_env_var(env, mini);
	*j = *j + ft_strlen(get_env_value(temp_env));
	return (get_env_value(temp_env));
}

int	replace_braces(t_token *temp, t_mini *mini)
{
	int		i;
	int		j;
	char	dest[2048];
	char	replace_temp;

	i = 0;
	while (i < 2048)
		dest[i++] = 0;
	i = 0;
	j = 0;
	while (temp->arg[i])
	{
		if (temp->arg[i] == 34)
		{
			temp->double_quote = !temp->double_quote;
			i++;
		}
		else if (temp->arg[i] == 39)
		{
			temp->single_quote = !temp->single_quote;
			i++;
		}
		if (temp->single_quote == 0 && temp->arg[i] == '$')
		{
			replace_temp = replace_by_env(mini, temp, &i, &j);
			ft_strlcat(dest, replace_temp, ft_strlen(replace_temp));
		}
		else
			dest[j++] = temp->arg[i++];
	}
	return (0);
}

int	purge_token(t_mini *mini)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = mini->token;
	while (temp)
	{
		replace_braces(temp, mini);
		temp = temp->next;
	}
}

void	lexer(t_mini *mini)
{
	t_token	*temp;

	temp = mini->token;
	purge_token(mini);
	
}
