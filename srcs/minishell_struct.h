/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 09:06:28 by matthieu          #+#    #+#             */
/*   Updated: 2021/11/26 10:20:42 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include "minishell.h"

enum	e_etat
{
	redirection_in = 0,
	redirection_out,
	heredoc,
	pipe,
	litteral,
}	e_etat;

typedef struct s_redir
{
	char			*type;
	char			*file;
	int				fd;
	struct s_redir	*next;
}					t_redir;

typedef struct s_arg
{
	char			*content;
	struct s_arg	*next;
}					t_arg;

typedef struct s_index_redir
{
	int		heredoc;
	int		infile;
	int		outfile;
}					t_index_redir;

typedef struct s_exec
{
	t_arg					*arg;
	t_redir					*redir;
	char					*heredoc;
	int						infile_fd;
	int						outfile_fd;
	int						return_value;
	struct s_index_redir	index;
	struct s_exec			*next;
}					t_exec;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*arg;
	int				single_quote;
	int				double_quote;
	e_etat			etat;
	struct s_token	*next;
}			t_token;

typedef struct s_mini
{
	struct s_env	*env;
	struct s_exec	*exec;
	struct s_token	*token;
	int				last_return_value;
}					t_mini;

#endif
