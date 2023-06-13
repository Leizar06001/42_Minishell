/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:09 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/13 19:35:24 by rloussig         ###   ########.fr       */
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
    while (str[i] && !ft_isspace(str[i]))
        i++;
    word = (char *)malloc(sizeof(char) * (i + 1));
    i = 0;
    while (str[i] && !ft_isspace(str[i]))
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
    int i;

    i = 0;
    while (str[i] && str[i] != '"')
        i++;
    word = (char *)malloc(sizeof(char) * (i + 1));
    if (!word)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '"')
    {
        word[i] = str[i];
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
        while (*str && ft_isspace(*str))
            str++;
        if (*str && *str == '"')
        {
            arr[i++] = malloc_word_quote(++str);
            while (*str && *str != '"')
                str++;
            str++;
        }
        else if (*str && !ft_isspace(*str))
        {
            arr[i++] = malloc_word(str);
            while (*str && !ft_isspace(*str))
                str++;
        }
    }
    arr[i] = NULL;
    get_env_var(arr);
    return (arr);
}
