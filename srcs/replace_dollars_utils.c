/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:02:00 by rloussig          #+#    #+#             */
/*   Updated: 2023/08/09 17:06:40 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_arg_name_end(char *arg)
{
	int	i;

	i = 0;
	while ((arg[i] > 'a' && arg[i] < 'z') || (arg[i] > 'A' && arg[i] < 'Z')
		|| (arg[i] > '0' && arg[i] < '9'))
		i++;
	return (i);
}

char	*replace_interogation(char *tmp)
{
	free(tmp);
	return (ft_itoa(g_data.exit_status));
}

char	*remove_quote_inside(char *arg)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	while (arg[++i])
	{
		if (arg[i] != '\'')
			j++;
	}
	tmp = (char *)malloc(sizeof(char) * (j + 1));
	j = 0;
	i = 0;
	while (arg[j])
	{
		if (arg[j] != '\'')
		{
			tmp[i] = arg[j];
			i++;
		}
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}
