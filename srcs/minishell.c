/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:39:04 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/31 14:57:26 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/get_next_line.h"

void	free_all_main(t_mini *mini)
{
	rl_clear_history();
	ft_free_env(mini);
	free_lst_exec(mini);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_mini		mini;

	if (ac || av)
	{
		if (init_mini_struct(&mini, env))
			return (1);
		while (1)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, &sigint_handler);
			line = readline("$minishell> ");
			if (ft_strlen(line) > 0)
				add_history(line);
			if (line)
			{
				parsing(&mini, line);
				free(line);
			}
			else
				exit(130);
		}
		free_all_main(&mini);
	}
	return (1);
}
