#ifndef PIPEH_H
# define PIPEH_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_data
{
    char	**path_fnc;
    char	**path_lst;
    int     orig_fd_in;
    int     orig_fd_out;
}               t_data;

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);

#endif
