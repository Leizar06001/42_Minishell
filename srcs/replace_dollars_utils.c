/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:02:00 by rloussig          #+#    #+#             */
/*   Updated: 2023/08/09 16:14:28 by rloussig         ###   ########.fr       */
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
