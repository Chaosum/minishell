/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:23:26 by mservage          #+#    #+#             */
/*   Updated: 2021/10/18 17:49:31 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(const char s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_risinside(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	i--;
	while (ft_ischarset(s1[i], set))
		i--;
	return (i);
}

static int	ft_isinside(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (ft_ischarset(s1[i], set) && s1[i])
		i++;
	return (i);
}

static char	*check_error(char *temp)
{
	temp = malloc(sizeof(char) * 1);
	if (temp == NULL)
		return (NULL);
	temp[0] = 0;
	return (temp);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i[3];
	char	*temp;

	temp = NULL;
	i[1] = 0;
	i[2] = 0;
	if (!(s1 && set))
		return (0);
	i[0] = ft_isinside(s1, set);
	if (s1[i[0]] == 0)
	{
		temp = check_error(temp);
		if (temp == NULL)
			return (NULL);
		return (temp);
	}
	while (s1[i[1]])
		i[1]++;
	i[1] = ft_risinside(s1 + i[0], set);
	temp = ft_calloc((i[1] + 2), sizeof(char));
	if (temp == NULL)
		return (NULL);
	while (i[2] <= i[1])
		temp[i[2]++] = s1[i[0]++];
	return (temp);
}
