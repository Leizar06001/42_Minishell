/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:01:01 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/24 19:37:42 by raphaellous      ###   ########.fr       */
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
        g_data.line = ft_strjoin(g_data.line, tmp);
        if (!ft_strcmp(tmp, "\""))
            g_data.line = ft_strjoin(g_data.line, "\n");
        str = g_data.line;
    }
    return (0);
}
