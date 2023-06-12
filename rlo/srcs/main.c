/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/12 19:28:48 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data  *datas;

size_t  ft_strlen(const char *s)
{
    size_t  i;

    i = 0;
    while (s[i] != '\0')
        i++;
    return (i);
}

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t      i;
    char        *p1;
    char        *p2;

    i = 0;
    p1 = (char *)dest;
    p2 = (char *)src;
    if (p1 == NULL && p2 == NULL)
        return (NULL);
    while (i < n)
    {
        p1[i] = p2[i];
        i++;
    }
    return (dest);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
    char    *buffer;

    if (!s1 || !s2)
        return (NULL);
    buffer = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
    if (!buffer)
        return (NULL);
    ft_memcpy(buffer, s1, ft_strlen(s1));
    ft_memcpy(buffer + ft_strlen(s1), s2, ft_strlen(s2));
    buffer[ft_strlen(s1) + ft_strlen(s2)] = '\0';
    return (buffer);
}

int find_fnc_path(char *fnc_name, char **path_lst, int index)
{
    int     i;
    char    *tmp;

    (void)index;
    i = 0;
    while (path_lst[i])
    {
        tmp = ft_strjoin(path_lst[i], fnc_name);
        if (access(tmp, F_OK) == 0)
        {
            printf("%d > %s : %s\n", index, fnc_name, tmp);
            //ft_memcpy(datas->path_fnc[index], tmp, ft_strlen(tmp));
            datas->path_fnc = tmp;
            return (1);
        }
        //free(tmp);
        i++;
    }
    return (0);
}

void    find_sys_functions(void)
{
    char    *path;
    char    **path_lst;

    path = getenv("PATH");
    path_lst = ft_split(path, ':');
    find_fnc_path("/chdir", path_lst, 0);
    find_fnc_path("/echo", path_lst, 1);
    find_fnc_path("/pwd", path_lst, 2);
    find_fnc_path("/export", path_lst, 3);
    find_fnc_path("/unset", path_lst, 4);
    find_fnc_path("/env", path_lst, 5);
    find_fnc_path("/exit", path_lst, 6);
}

int main()
{
	// char *minishell_name;
	// char * user;
	// char *result;
    datas->popo = 10;
    printf("%d\n", datas->popo);
    find_sys_functions();


	// user = getenv("USER");
	// minishell_name = ft_strjoin(user, "@minishell : ");
    // while (1){
    // 	result = readline(minishell_name);
    // 	add_history (result);

    // 	printf("%s\n", result);
    // }
}
