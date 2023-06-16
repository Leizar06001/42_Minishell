/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:36:36 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/15 16:05:12 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    **ft_arraydup(char **arr)
{
    int i;
    char **new_arr;

    i = -1;
    new_arr = malloc(sizeof(char *) * (ft_size_array(arr) + 2));
    while (arr[++i])
        new_arr[i] = ft_strdup(arr[i]);
    new_arr[++i] = NULL;
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
