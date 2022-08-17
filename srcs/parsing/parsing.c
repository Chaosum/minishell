/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:25:46 by rjeannot          #+#    #+#             */
/*   Updated: 2022/02/03 14:16:34 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signal;

char	*replace_by_env_ret(char *env, t_env *temp_env, int *j)
{
	free(env);
	env = get_env_value(temp_env);
	*j = *j + ft_strlen(env);
	return (env);
}

void	parsing(t_mini *mini, char *line)
{
	g_signal = 0;
	if (start_token(line, mini) == 0)
	{
		if (lexer(mini) == 0)
			ft_execution(mini);
	}
}
