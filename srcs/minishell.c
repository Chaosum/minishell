/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:39:04 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/29 16:41:39 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/get_next_line.h"



int	main(int ac, char **av, char **env)
{
	char		*line;
	t_mini		mini;

	if (ac || av)
	{
		init_mini_struct(&mini, env);
		if (init_shell_level(&mini))
		{
			ft_free_env(&mini);
			return (1);
		}
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
		rl_clear_history();
		ft_free_env(&mini);
		free_lst_exec(&mini);
		return (1);
	}
}
