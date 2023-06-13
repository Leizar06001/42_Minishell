/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:03:55 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/12 19:29:20 by rloussig         ###   ########.fr       */
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

typedef struct	s_fnc_path
{
	char	cd[255];
	char	echo[255];
	char	pwd[255];
}				t_fnc_path;

//STRUCTURE
typedef struct s_data
{
	//t_fnc_path	*paths;
	char		*user;
	char		*path;
	char		*minishell_name;
	char		*line;
	//char		path_fnc[10][255];
	char		*path_fnc;
	int			popo;
}		t_data;

//FT_STRJOIN
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

#endif
