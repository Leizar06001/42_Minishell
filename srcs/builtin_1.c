/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:41:56 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/14 13:45:36 by rloussig         ###   ########.fr       */
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

void    ft_env()
{
    int i;

    i = -1;
    while (data.env[++i])
        printf("%s\n", data.env[i]);
}

void    ft_export(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        printf(">%s<\n", cmd[i]);
        i++;
    }
    printf("%d\n", i);
}

void    ft_unset(char **cmd)
{
    (void)cmd;
}
