/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:19:18 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/13 20:19:20 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(char **input)
{
    int i = 1;
    int option;
    if (ft_strcmp(input[1], "-n") == 0)
    {
        option = 1;
        i = 2;
    }
    while(input[i])
    {
        if (input[i + 1] == NULL)
            printf("%s", input[i]);
        else
            printf("%s ", input[i]);
        i++;
    }
    if (option != 1)
        printf("\n");
}
