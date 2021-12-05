/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:09:44 by rjeannot          #+#    #+#             */
/*   Updated: 2021/12/05 04:13:53 by matthieu         ###   ########.fr       */
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
	char	*replace_temp;

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
		else if (temp->single_quote == 0 && temp->arg[i] == '$')
		{
			replace_temp = replace_by_env(mini, temp, &i, &j);
			ft_strlcat(dest, replace_temp, ft_strlen(replace_temp));
		}
		else
			dest[j++] = temp->arg[i++];
	}
	free(temp->arg);
	temp->arg = ft_strdup(dest);
	if (temp->arg == NULL)
	{
		printf("malloc error\n");
		return (1);
	}
	return (0);
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

int	check_token_redir(t_mini *mini, t_token *temp)
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
int	parse_token(t_mini *mini)
{
	t_token	*temp;

	temp = mini->token;
	while (temp)
	{
		if (temp->etat == 0 || temp->etat == 1 || temp->etat == 2)
		{
			check_token_redir(mini, temp);
		}
		else if (temp->etat != is_pipe)
			temp->etat = litteral;
		temp = temp->next;
	}
	return (0);
}

int	create_redir(t_mini *mini, t_exec *exec, t_token *temp)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (temp->etat == 0)
	{
		redir->type = ft_strdup("<");
		if (temp->next)
			redir->file = ft_strdup(temp->next->arg);
		ft_lstadd_back_redir(&exec->redir, redir);
	}
	if (temp->etat == 1)
	{
		redir->type = ft_strdup(">");
		if (temp->next)
			redir->file = ft_strdup(temp->next->arg);
		ft_lstadd_back_redir(&exec->redir, redir);
	}
	if (temp->etat == 2)
	{
		redir->type = ft_strdup(">>");
		if (temp->next)
			redir->file = ft_strdup(temp->next->arg);
		ft_lstadd_back_redir(&exec->redir, redir);
	}
	if (temp->etat == 3)
	{
		redir->type = ft_strdup("<<");
		if (temp->next)
			redir->file = ft_strdup(temp->next->arg);
		ft_lstadd_back_redir(&exec->redir, redir);
	}
}

int	create_exec(t_mini *mini)
{
	t_exec	*temp;

	temp = ft_calloc(1, sizeof(t_exec));
	if (temp == NULL)
	{
		printf("Malloc error\n");
		return (1);
	}
	ft_lstadd_back_exec(&mini->exec, temp);
	return (0);
}

int	create_arg(t_mini *mini, t_exec *exec, t_token *temp)
{
	t_arg	*arg;

	arg = ft_calloc(1, sizeof(t_arg));
	if (arg == NULL)
	{
		printf("Malloc error\n");
		return (1);
	}
	arg->content = ft_strdup(temp->arg);
	if (arg->content == NULL)
	{
		printf("Malloc error\n");
		return (1);
	}
	ft_lstadd_back_arg(&exec->arg, arg);
	return (0);
}

int	lexer_exec(t_mini *mini)
{
	t_token	*temp;
	t_exec	*temp_exec;

	temp = mini->token;
	if (temp)
	{
		create_exec(mini);
		temp_exec = mini->exec;
	}
	if (mini->exec == NULL)
	{
		printf("Malloc error\n");
		return (1);
	}
	while (temp)
	{
		if (temp->etat < 4)
		{
			create_redir(mini, temp_exec, temp);
			temp = temp->next;
			if (temp)
				temp = temp->next;
		}
		else if (temp->etat == is_pipe)
		{
			create_exec(mini);
			temp_exec = temp_exec->next;
			temp = temp->next;
		}
		else
		{
			create_arg(mini, temp_exec, temp);
			temp = temp->next;
		}
	}
}

void	lexer(t_mini *mini)
{
	t_token	*temp;

	temp = mini->token;
	purge_token(mini);
	print_token(mini);
	parse_token(mini);
	lexer_exec(mini);
}
