/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:07:58 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/13 19:15:11 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t		i;
	int			j;
	char		diff;

	if (((to_find == 0 || str == 0) && len == 0) || !ft_strlen(to_find))
		return ((char *)str);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		diff = 0;
		while (str[i + j] && !diff && i + j < len)
		{
			if (!to_find[j])
				return ((char *)(str + i));
			else if (!(to_find[j] == str[i + j]))
				diff = 1;
			j++;
		}
		if (!diff && !to_find[j])
			return ((char *)(str + i));
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}
