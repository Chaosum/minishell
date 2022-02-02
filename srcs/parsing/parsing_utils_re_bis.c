/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_re_bis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:03:55 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/02 17:13:48 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env->value[i] != '=' && env->value[i])
			i++;
		i++;
		return (&env->value[i]);
	}
	return (NULL);
}

char	*return_value_case(t_mini *mini, int *i)
{
	char	*env;

	env = ft_itoa(mini->last_return_value);
	*i = *i + 1;
	return (env);
}

char	*replace_by_env(t_mini *mini, t_token *temp, int *i, int *j)
{
	char	*env;
	t_env	*temp_env;
	int		k;

	k = *i;
	if (temp->arg[*i] == '?')
		return (return_value_case(mini, i));
	while (temp->arg[k] && (ft_isalnum(temp->arg[k]) && temp->arg[k] != '_'))
		k++;
	env = ft_calloc(k + 1, sizeof(char));
	k = 0;
	while (temp->arg[*i] && (ft_isalnum(temp->arg[*i]) && temp->arg[k] != '_'))
	{
		env[k] = temp->arg[*i];
		*i = *i + 1;
		k++;
	}
	temp_env = get_env_var(env, mini);
	if (temp_env == NULL)
	{
		*j = *j + 1;
		return ("");
	}
	*j = *j + ft_strlen(get_env_value(temp_env));
	return (get_env_value(temp_env));
}

void	print_token(t_mini *mini)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = mini->token;
	while (temp)
	{
		printf("%d : %s\n", i++, temp->arg);
		temp = temp->next;
	}
}

int	check_token_redir(t_token *temp)
{
	if (temp->next)
	{
		if (temp->etat == redirection_in || temp->etat == heredoc)
		{
			if (temp->next->etat != -1)
			{
				printf("parse error near <\n");
				return (1);
			}
			else
				temp->next->etat = litteral;
		}
		else if (temp->etat == redirection_out
			|| temp->etat == redirection_out_append)
		{
			if (temp->next->etat != -1)
			{
				printf("parse error near >\n");
				return (1);
			}
			else
				temp->next->etat = litteral;
		}
	}
	return (0);
}
