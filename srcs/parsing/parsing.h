/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:27:06 by rjeannot          #+#    #+#             */
/*   Updated: 2022/01/29 16:28:28 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

/* lexer.c */

char	*get_env_value(t_env *env);
char	*replace_by_env(t_mini *mini, t_token *temp, int *i, int *j);
int		replace_braces(t_token *temp, t_mini *mini);
void	print_token(t_mini *mini);
int		purge_token(t_mini *mini);
int		check_token_redir(t_token *temp);
int		parse_token(t_mini *mini);
int		create_redir(t_exec *exec, t_token *temp);
int		create_arg(t_exec *exec, t_token *temp);
int		lexer_exec(t_mini *mini);
void	free_lexer(t_mini *mini);
int		lexer(t_mini *mini);

/* parsing_utils */
int		ft_isspace(char c);
void	ft_token_add_back(t_token **alst, t_token *new);
void	ft_lstadd_back_exec(t_exec **alst, t_exec *new);
void	ft_lstadd_back_redir(t_redir **alst, t_redir *new);
void	ft_lstadd_back_arg(t_arg **alst, t_arg *new);


/* tokenizer */
int		create_redir_token(t_mini *mini, char *line, int *i);
int		create_token(t_mini *mini, char *line, int start, int max);
int		is_token(int double_quote, int single_quote, int i, char *line);
int		is_redir(int double_quote, int single_quote, int i, char *line);
void	skip_isspace(char *line, int *i, int *prev);
int		start_token(char *line, t_mini *mini);

/* parsing.c */

void	parsing(t_mini *mini, char *line);

#endif