/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:25:43 by mservage          #+#    #+#             */
/*   Updated: 2021/10/13 02:22:12 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_mini *mini, t_arg *prms)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	printf("%s\n", path);
	mini->exec->return_value = 0;
	return ;
}
