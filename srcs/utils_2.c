/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:19:23 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/24 19:48:30 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (c == '\0')
		return ((char *)(s + ft_strlen(s)));
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (c);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || (c >= '0' && c <= '9'))
		return (c);
	return (0);
}

int	ft_size_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	get_env_var(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (ft_strchr(arr[i], '$'))
			arr[i] = getenv(arr[i] + 1);
	}
}
