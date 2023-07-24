/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:46:41 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/24 19:37:42 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    add_str_to_output(char *str)
{
    char *tmp;

    if (g_data.output == NULL)
        g_data.output = ft_strdup(str);
    else
    {
        tmp = ft_strjoin(g_data.output, str);
        free(g_data.output);
        g_data.output = tmp;
    }
}

void    clear_output()
{
    if (g_data.output)
        free(g_data.output);
    g_data.output = NULL;
}

void    select_output(char **cmd_line)
{
    int i;

    i = 0;
    while (cmd_line[i])
    {
        if (!ft_strcmp(cmd_line[i], ">") || !ft_strcmp(cmd_line[i], ">>"))
        {
            ft_redir_output(cmd_line);
            return ;
        }
        i++;
    }
    if (g_data.output)
        printf("%s", g_data.output);
    clear_output();
}
