/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:09 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/19 11:01:20 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
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
    char *tmp;

    i = 0;
    tmp = str;
    while(str[i] && !ft_isspace(str[i]))
    {
        if (str[i] == '"')
            str++;
        while (str[i] && !ft_isspace(str[i]) && str[i] != '"')
            i++;
        if(str[i] == '"')
            str++;
    }
    while (str[i] && !ft_isspace(str[i]) && str[i] != '"')
        i++;
    word = (char *)malloc(sizeof(char) * (i + 1));
    i = 0;
    str = tmp;
    while (str[i] && !ft_isspace(str[i]))
    {
        if (str[i] == '"')
            str++;
        while (str[i] && !ft_isspace(str[i]) && str[i] != '"')
        {
            word[i] = str[i];
            i++;
        }
        if (str[i] == '"')
            str++;
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
        if (*str == '"')
            str++;
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
            str++;
    }
    word[i] = '\0';
    return (word);
}


char    **ft_split_spaces(char *str)
{
    char    **arr;
    int     i = 0;

    arr = (char **)malloc(sizeof(char *) * (count_words(str) + 1));
    if (!arr)
        return (NULL);
    while (*str)
    {
        if (*str && *str == '\"')
        {
            arr[i++] = malloc_word_quote(++str);

            while (*str)
            {
                if (*str == '"')
                    str++;
                while (*str != '\"')
                    str++;
                if (*str == '"')
                    str++;
            }
        }
        else if (*str && !ft_isspace(*str))
        {
            if (data.testdquote == 0)
            {
                arr[i++] = malloc_word(str);
                while (*str && !ft_isspace(*str) && *str != '\"')
                    str++;
                while (*str && ft_isspace(*str))
                    str++;
                data.testdquote = 1;
            }

            else
            {
                arr[i++] = malloc_word(str);
                while (*str)
                {
                    if (*str == '"')
                        str++;
                    while (*str && !ft_isspace(*str))
                       str++;
                    if (*str == '"')
                        str++;
                    while (*str && ft_isspace(*str))
                        str++;
                }
                data.testdquote = 0;
            }
        }
    }
    arr[i] = NULL;
    get_env_var(arr);
    return (arr);
}

*/  


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
    char    *word;
    int     len;
    int     i;

    len = 0;
    i = 0;
    while(str[len] && !ft_isspace(str[len]) && str[len] != '\"')
            len++;
    word = (char *)malloc(sizeof(char) * (len + 1));
    while (str[i] && !ft_isspace(str[i]) && str[i] != '\"')
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
    int len;

    len = 1;
    i = 0;
    while (str[len] && str[len] != '\"')
            len++;
    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    while (str[i] && str[i] != '\"')
    {
            word[i] = str[i];
            i++;
    }
    word[i++] = '\"';
    word[i] = '\0';
    return (word);
}


char    **ft_split_spaces(char *str)
{
    char    **arr;
    int     i = 0;

    arr = (char **)malloc(sizeof(char *) * (count_words(str) + 1));
    if (!arr)
        return (NULL);
    while (*str)
    {
        if (*str && *str == '\"')
        {
            arr[i++] = malloc_word_quote(++str);
            while (*str)
            {
                if (*str == '"')
                    str++;
                while (*str != '\"')
                    str++;
                if (*str == '"')
                    str++;
            }
        }
        else if (*str && !ft_isspace(*str))
        {
            arr[i++] = malloc_word(str);
            while (*str && !ft_isspace(*str) && *str != '\"')
                str++;
        }
        else if (*str && ft_isspace(*str))
            str++;
    }
    arr[i] = NULL;
    get_env_var(arr);
    return (arr);
}
