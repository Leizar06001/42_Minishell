/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/12 18:05:56 by mabdali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

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

void	init_struct(t_data *data)
{
	
}

int main()
{
	char *minishell_name;
	char * user;
	char *result;
	
	user = getenv("USER");
	minishell_name = ft_strjoin(user, "@minishell : ");
	result = readline(minishell_name);
	add_history (result);

	printf("%s", result);
}