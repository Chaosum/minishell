/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 09:06:28 by matthieu          #+#    #+#             */
/*   Updated: 2021/09/28 15:20:45 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include "minishell.h"

typedef struct s_redir
{
	char			*type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_arg
{
	char			*content;
	struct s_arg	*next;
}					t_arg;

typedef struct s_exec
{
	t_arg			*arg;
	t_redir			*redir;
	struct s_exec	*next;
}					t_exec;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_mini
{
	struct s_env	*env;
	struct s_exec	*exec;
}					t_mini;

#endif
