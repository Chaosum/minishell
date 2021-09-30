/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:45:31 by matthieu          #+#    #+#             */
/*   Updated: 2021/09/30 02:45:12 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

void	ft_execution(t_mini *mini);
void	ft_redir_infile(t_mini *mini, t_exec *exec);
void	ft_redir_outfile(t_mini *mini, t_exec *exec, int append);

#endif