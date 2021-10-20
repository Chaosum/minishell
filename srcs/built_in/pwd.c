/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:43 by mservage          #+#    #+#             */
/*   Updated: 2021/10/19 19:23:46 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_mini *mini, t_arg *prms)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	write(mini->exec->outfile_fd, path, ft_strlen(path));
	printf("%s\n", path);
	mini->exec->return_value = 0;
	return ;
}
