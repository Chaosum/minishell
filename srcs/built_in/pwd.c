/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:43 by mservage          #+#    #+#             */
/*   Updated: 2022/01/27 14:56:30 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_mini *mini, t_arg *prms)
{
	char	path[PATH_MAX];

	if (prms)
		;
	getcwd(path, PATH_MAX);
	write(mini->exec->outfile_fd, path, ft_strlen(path));
	printf("%s\n", path);
	mini->exec->return_value = 0;
	return ;
}
