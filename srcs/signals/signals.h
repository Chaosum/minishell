/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:31:51 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/02 17:18:01 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../minishell.h"

/* signals.c */

void	sigint_handler_cat(int signum);
void	sigint_handler_quit(int signum);
void	sigint_handler(int signum);
void	sigint_handler_heredoc(int signum);

#endif