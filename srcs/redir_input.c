/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:15:42 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/19 13:15:56 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_read_from_file(char *filename)
{
    int     fd;
    char    *line;

    fd = open(filename, O_RDONLY);
    while (get_next_line(fd, &line))
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
}
