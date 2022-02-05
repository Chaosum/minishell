/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:39:04 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/04 15:30:03 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/get_next_line.h"

int	g_signal = 0;

void	free_all_main(t_mini *mini)
{
	rl_clear_history();
	ft_free_env(mini);
	free_lst_exec(mini);
}

void	free_all_main_d(t_mini *mini)
{
	rl_clear_history();
	ft_free_env(mini);
	free_lst_exec(mini);
	printf("exit\n");
	exit (0);
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
			printf("%s\n", line);
			if (ft_strlen(line) > 0)
				add_history(line);
			if (line)
			{
				parsing(&mini, line);
				free(line);
			}
			else
				free_all_main_d(&mini);
		}
		free_all_main(&mini);
	}
	return (1);
}
