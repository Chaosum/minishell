/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_re_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:08:19 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/31 16:09:00 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_exec(t_mini *mini)
{
	t_exec	*temp;

	temp = ft_calloc(1, sizeof(t_exec));
	if (temp == NULL)
	{
		printf("Malloc error\n");
		return (1);
	}
	temp->outfile_fd = 1;
	ft_lstadd_back_exec(&mini->exec, temp);
	return (0);
}

int	create_arg(t_exec *exec, t_token *temp)
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
