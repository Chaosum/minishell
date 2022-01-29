/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:31:51 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/29 16:31:54 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/* signals.c */

void	sigint_handler_cat(int signum);
void	sigint_handler_quit(int signum);
void	sigint_handler(int signum);
void	sigint_handler_heredoc(int signum);

#endif