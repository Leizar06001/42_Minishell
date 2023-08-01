/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:25:03 by raphaellous       #+#    #+#             */
/*   Updated: 2023/08/01 16:20:09 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_arrows(char *str)
{
	if (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0)
		return (1);
	else
		return (0);
}

int	str_only_space_tab(char *str)
{
	char	c;
	int		i;

	i = -1;
	while (str[++i])
	{
		c = str[i];
		if (c != '\t' && c != '\n' && c != '\b' && c != '\v'
			&& c != '\f' && c != '\r' && c != ' ')
			return (0);
	}
	return (1);
}

void	*ft_calloc(size_t nb, size_t size)
{
	char	*res;
	size_t	i;

	res = malloc(nb * size);
	if (!res)
		return (0);
	i = 0;
	while (i < nb * size)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}
