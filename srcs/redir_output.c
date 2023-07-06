/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:56:50 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/20 13:16:25 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_write_to_file(char *filename, char *str)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, str, ft_strlen(str));
    close(fd);
}

void    ft_append_to_file(char *filename, char *str)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    write(fd, str, ft_strlen(str));
    close(fd);
}

void    ft_redir_output(char **cmd_line)
{
    int     i;
    int     j;
    char    *filename;

    i = 0;
    while (cmd_line[i])
    {
        printf("cmd_line[%d] = %s\n", i, cmd_line[i]);
        if (!ft_strcmp(cmd_line[i], ">"))
        {
            filename = cmd_line[i + 1];
            j = i;
            while (cmd_line[j])
            {
                cmd_line[j] = cmd_line[j + 2];
                j++;
            }
            ft_write_to_file(filename, cmd_line[0]);
            return ;
        }
        else if (!ft_strcmp(cmd_line[i], ">>"))
        {
            filename = cmd_line[i + 1];
            j = i;
            while (cmd_line[j])
            {
                cmd_line[j] = cmd_line[j + 2];
                j++;
            }
            ft_append_to_file(filename, cmd_line[0]);
            return ;
        }
        i++;
    }
}
