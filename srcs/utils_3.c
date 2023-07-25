/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:36:36 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/25 17:36:56 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_arraydup_plus_one(char **arr)
{
	int		i;
	char	**new_arr;

	i = -1;
	new_arr = malloc(sizeof(char *) * (ft_size_array(arr) + 2));
	if (!new_arr)
		return (NULL);
	while (arr[++i])
		new_arr[i] = ft_strdup(arr[i]);
	new_arr[i] = NULL;
	return (new_arr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}

char	*ft_getenv(char *var)
{
	char	*value;

	value = getenv(var);
	if (!value)
		return ("");
	else
		return (value);
}
