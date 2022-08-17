/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:31:08 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/03 14:11:18 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signal;

void	sigint_handler(int signum)
{
	if (signum)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigint_handler_cat(int signum)
{
	if (signum)
	{
		g_signal = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	sigint_handler_quit(int signum)
{
	if (signum)
	{
		g_signal = 1;
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	sigint_handler_heredoc(int signum)
{
	if (signum)
	{
		g_signal = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(130);
	}
}
