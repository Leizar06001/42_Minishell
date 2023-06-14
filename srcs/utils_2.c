/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:19:23 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/13 20:19:23 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void get_env_var(char **arr)
{
    int i;

    i = -1;
    while (arr[++i])
    {
        if (strchr(arr[i], '$'))
            arr[i] = getenv(arr[i] + 1);
    }
}