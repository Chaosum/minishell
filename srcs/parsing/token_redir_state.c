/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:09:34 by matthieu          #+#    #+#             */
/*   Updated: 2022/01/31 16:15:06 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	state_redirection_in(t_exec *exec, t_token *temp, t_redir *redir)
{
	redir->type = ft_strdup("<");
	if (temp->next)
		redir->file = ft_strdup(temp->next->arg);
	ft_lstadd_back_redir(&exec->redir, redir);
}

void	state_redirection_out(t_exec *exec, t_token *temp, t_redir *redir)
{
	redir->type = ft_strdup(">");
	if (temp->next)
		redir->file = ft_strdup(temp->next->arg);
	ft_lstadd_back_redir(&exec->redir, redir);
}

void	state_redirection_out_app(t_exec *exec, t_token *temp, t_redir *redir)
{
	redir->type = ft_strdup(">>");
	if (temp->next)
		redir->file = ft_strdup(temp->next->arg);
	ft_lstadd_back_redir(&exec->redir, redir);
}

void	state_redirection_heredoc(t_exec *exec, t_token *temp, t_redir *redir)
{
	redir->type = ft_strdup("<<");
	if (temp->next)
		redir->file = ft_strdup(temp->next->arg);
	ft_lstadd_back_redir(&exec->redir, redir);
}

int	create_redir(t_exec *exec, t_token *temp)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (temp->etat == redirection_in)
		state_redirection_in(exec, temp, redir);
	if (temp->etat == redirection_out)
		state_redirection_out(exec, temp, redir);
	if (temp->etat == redirection_out_append)
		state_redirection_out_app(exec, temp, redir);
	if (temp->etat == heredoc)
		state_redirection_heredoc(exec, temp, redir);
	return (0);
}
