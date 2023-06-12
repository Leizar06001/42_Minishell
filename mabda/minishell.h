/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:03:55 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/12 18:09:06 by mabdali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

//STRUCTURE
typedef struct s_data
{
	char *user;
	char *minishell_name;
	char *line;
}		t_data;

//FT_STRJOIN
size_t  ft_strlen(const char *s);
void    *ft_memcpy(void *dest, const void *src, size_t n);
char    *ft_strjoin(char const *s1, char const *s2);


# endif
