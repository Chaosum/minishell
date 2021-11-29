/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:27:06 by rjeannot          #+#    #+#             */
/*   Updated: 2021/11/26 10:40:43 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* parsing_utils */
int		ft_isspace(char c);
void	ft_token_add_back(t_token **alst, t_token *new);

/* tokenizer */
int		start_token(char *line, t_mini *mini);
void	create_token(t_mini *mini,
			t_token *token, char *line, int start, int max);
t_token	*init_token(void);

#endif 