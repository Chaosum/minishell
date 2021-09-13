/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 09:06:28 by matthieu          #+#    #+#             */
/*   Updated: 2021/09/10 13:52:48 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include "minishell.h"

typedef struct s_malloc
{
	char	**env;
}		t_malloc;

typedef struct s_history
{
	char				*string;
	struct t_history	*previous;
	struct t_history	*next;
}				t_history;

typedef struct s_mini
{
	char		**env;
	t_malloc	malloced;
}				t_mini;

#endif
