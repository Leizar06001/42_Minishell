/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:36:36 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/28 19:06:13 by raphaellous      ###   ########.fr       */
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

static int	ft_nb_char(long n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	ln;
	int		len;
	char	*str;

	ln = (long) n;
	len = ft_nb_char(ln);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	if (ln < 0)
		ln = -ln;
	while (--len >= 0)
	{
		str[len] = (ln % 10) + '0';
		ln /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
