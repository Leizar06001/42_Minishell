/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:09 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/14 14:42:42 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int         ft_isspace(char c)
{
    return (c == ' ' || c == '\n' || c == '\t');
}

int     count_words(char *str)
{
    int count;

    count = 0;
    while (*str)
    {
        while (*str && ft_isspace(*str))
            str++;
        if (*str && !ft_isspace(*str))
        {
            count++;
            while (*str && !ft_isspace(*str))
                str++;
        }
    }
    return (count);
}

char    *malloc_word(char *str)
{
    char *word;
    int i;

    i = 0;
    while (str[i] && !ft_isspace(str[i]) && str[i] != '"')
        i++;
    word = (char *)malloc(sizeof(char) * (i + 1));
    i = 0;
    while (str[i] && !ft_isspace(str[i]) && str[i] != '"')
    {
        word[i] = str[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}


char    *malloc_word_quote(char *str)
{
    char *word;
    int size;
    int i;

    size = 0;
    i = 0;
    char    *tmp = str;
    while (*str)
    {
        while (*str && *str != '"')
        {
            size++;
            str++;
        }
        if (*str == '"')
            str++;
    }
    word = (char *)malloc(sizeof(char) * (size + 1));
    if (!word)
        return (NULL);
    i = 0;
    str = tmp;
    while (str[i])
    {
        while (str[i] && str[i] != '"')
        {
            word[i] = str[i];
            i++;
        }
        if (str[i] == '"')
            i++;
    }
    word[i] = '\0';
    return (word);
}


char    **ft_split_spaces(char *str)
{
    char **arr;
    int i = 0;

    arr = (char **)malloc(sizeof(char *) * (count_words(str) + 1));
    if (!arr)
        return (NULL);
    while (*str)
    {
        if (*str && *str == '\"')
        {
            arr[i++] = malloc_word_quote(++str);
            while (*str && *str != '\"')
                str++;
            str++;
        }
        else if (*str && !ft_isspace(*str))
        {
            arr[i++] = malloc_word(str);
            while (*str && !ft_isspace(*str) && *str != '\"')
                str++;
        }
        while (*str && ft_isspace(*str))
             str++;
    }
    arr[i] = NULL;
    get_env_var(arr);
    printf("arr[0] = %s\n", arr[0]);
    printf("arr[1] = %s\n", arr[1]);
    printf("arr[2] = %s\n", arr[2]);
    printf("arr[3] = %s\n", arr[3]);
    return (arr);
}
