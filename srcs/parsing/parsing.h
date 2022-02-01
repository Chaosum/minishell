/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:27:06 by rjeannot          #+#    #+#             */
/*   Updated: 2022/02/01 02:21:13 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

/* create_token.c */
int		create_pipe_case(t_mini *mini, t_token *token, int *i);
int		create_redir_out_case(t_token *token, char *line, int *i);
int		create_redir_in_case(t_token *token, char *line, int *i);
int		create_redir_token(t_mini *mini, char *line, int *i);

/* free_parsing.c */
int		token_malloc_error(t_mini *mini, int ret_value);
void	free_lexer(t_mini *mini);

/* lexer_re_bis.c */
int		create_exec(t_mini *mini);
int		create_arg(t_exec *exec, t_token *temp);

/* lexer_bis.c */
int		creating_redir(t_token *temp);
void	lexer_exec_treatment(t_mini *mini, t_exec *temp_exec, t_token *temp);
int		lexer_exec(t_mini *mini);

/* lexer.c */
int		parse_token(t_mini *mini);
int		replace_braces(t_token *temp, t_mini *mini, t_lexer_var v);
int		purge_token(t_mini *mini);
int		lexer(t_mini *mini);

/* parsing_utils_bis.c */
void	init_var_lexer(t_lexer_var *var);
int		is_token(int double_quote, int single_quote, int i, char *line);
void	skip_isspace(char *line, int *i, int *prev);
int		is_redir(int double_quote, int single_quote, int i, char *line);
void	init_t_token(t_token_var *var);

/* parsing_utils_re_bis.c */
char	*get_env_value(t_env *env);
char	*replace_by_env(t_mini *mini, t_token *temp, int *i, int *j);
void	print_token(t_mini *mini);
int		check_token_redir(t_token *temp);

/* parsing_utils.c */
int		ft_isspace(char c);
void	ft_token_add_back(t_token **alst, t_token *new);
void	ft_lstadd_back_exec(t_exec **alst, t_exec *new);
void	ft_lstadd_back_redir(t_redir **alst, t_redir *new);
void	ft_lstadd_back_arg(t_arg **alst, t_arg *new);

/* parsing.c */
void	parsing(t_mini *mini, char *line);

/* token_redir_state.c */
void	state_redirection_in(t_exec *exec, t_token *temp, t_redir *redir);
void	state_redirection_out(t_exec *exec, t_token *temp, t_redir *redir);
void	state_redirection_out_app(t_exec *exec, t_token *temp, t_redir *redir);
void	state_redirection_heredoc(t_exec *exec, t_token *temp, t_redir *redir);
int		create_redir(t_exec *exec, t_token *temp);

/* tokenizer.c */
int		create_token(t_mini *mini, char *line, int start, int max);
int		tokenizer(char *line, t_mini *mini, t_token_var *var);
int		start_token(char *line, t_mini *mini);

#endif