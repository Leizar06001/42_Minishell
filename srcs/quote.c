/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:01:01 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/14 16:20:14 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int odd_quote(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '\"')
            j++;
        i++;
    }
    if (j % 2 == 0)
        return (0);
    else
        return (1);
}

int quote_error(char *str)
{
    char *tmp;

    while (odd_quote(str) == 1)
    {
        tmp = readline("dquote> ");
        data.line = ft_strjoin(data.line, tmp);
        if (!ft_strcmp(tmp, "\""))
            data.line = ft_strjoin(data.line, "\n");
        str = data.line;
    }
    return (0);
} 