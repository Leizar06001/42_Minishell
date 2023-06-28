/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:46:41 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/20 13:16:25 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    add_str_to_output(char *str)
{
    char *tmp;

    if (data.output == NULL)
        data.output = ft_strdup(str);
    else
    {
        tmp = ft_strjoin(data.output, str);
        free(data.output);
        data.output = tmp;
    }
}

void    clear_output()
{
    if (data.output)
        free(data.output);
    data.output = NULL;
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
    if (data.output)
        printf("%s", data.output);
    clear_output();
}
