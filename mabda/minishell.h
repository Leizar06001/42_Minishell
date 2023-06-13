/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:03:55 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/13 12:43:42 by mabdali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <unistd.h>

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BLUE   "\e[34m"

//STRUCTURE
typedef struct s_data
{
	char	*user;
	char	*path;
	char	*minishell_name;
	char	*line;
	char	**path_fnc;
	char        *echo_path;
}		t_data;

//extern  t_data *data;

//FT_STRJOIN
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char    **ft_split(char const *s, char c);

#endif
