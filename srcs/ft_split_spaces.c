/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:09 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/19 16:35:23 by rloussig         ###   ########.fr       */
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
    char    *word;
    int     len;
    int     i;

    len = 0;
    i = 0;
    while(str[len] && !ft_isspace(str[len]) && str[len] != '\"' && str[len] != '>' && str[len] != '<')
            len++;
    word = (char *)malloc(sizeof(char) * (len + 1));
    while (str[i] && !ft_isspace(str[i]) && str[i] != '\"' && str[i] != '>' && str[i] != '<')
    {
            word[i] = str[i];
            i++;
    }
    if (str[i] == '\"')
        data.next_is_quote = 1;
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
    if (str[len] == '\"')
        len++;
    while (str[len] && str[len] != '\"')
            len++;
    if (str[len] == '\"')
        len++;
    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    while (/*str[i] && str[i] != '\"'*/ i < len)
    {
            word[i] = str[i];
            i++;
    }
    if (str[i] == '\"')
        data.prev_is_quote = 1;
    word[i] = '\0';
    return (word);
}



char    *malloc_word_quote2(char *str)
{
    char *word;
    int i;
    int len;

    len = 1;
    i = 0;
    if (str[len] == '\'')
        len++;
    while (str[len] && str[len] != '\'')
            len++;
    if (str[len] == '\'')
        len++;
    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    while (i < len)
    {
            word[i] = str[i];
            i++;
    }
    if (str[i] == '\'')
        data.prev_is_quote = 1;
    word[i] = '\0';
    return (word);
}


char *ft_strndup(char *str, int n)
{
    char *new;
    int i;

    i = 0;
    new = (char *)malloc(sizeof(char) * (n + 1));
    if (!new)
        return (NULL);
    while (str[i] && i < n)
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

char    **ft_split_spaces(char *str)
{
    char    **arr;
    int     i = 0;

    //initialisation sinon bug au deuxieme appel
    data.next_is_quote = 0;
	data.prev_is_quote = 0;

    arr = (char **)malloc(sizeof(char *) * (count_words(str) + 10));
    if (!arr)
        return (NULL);
    while (*str)
    {
        if (*str && *str == '\"')
        {
            arr[i++] = malloc_word_quote(str);  ///
            while (*str)
            {
                if (*str == '"')
                    str++;
                while (*str != '\"')
                    str++;
                if (*str == '"')
                {
                    str++;
                    break;
                }
            }
            if (data.next_is_quote == 1)
            {
                arr[i - 2] = ft_strjoin(arr[i - 2], arr[i - 1]);
                i--;
                data.next_is_quote = 0;
            }
        }

        else if (*str && *str == '\'')
        {
            arr[i++] = malloc_word_quote2(str);
            while (*str)
            {
                if (*str == '\'')
                    str++;
                while (*str != '\'')
                    str++;
                if (*str == '\'')
                {
                    str++;
                    break;
                }
            }
        }



        else if (*str && !ft_isspace(*str) && *str != '>' && *str != '<')
        {
            arr[i++] = malloc_word(str);
            while (*str && !ft_isspace(*str) && *str != '\"' && *str != '>' && *str != '<')
                str++;
            if (data.prev_is_quote == 1)
            {
                arr[i - 2] = ft_strjoin(arr[i - 2], arr[i - 1]);
                i--;
                data.prev_is_quote = 0;
            }
        }
        else if (*str && (*str == '>' || *str == '<'))
        {
            if (*str == '>' && *(str + 1) == '>')
            {
                arr[i++] = ft_strdup(">>");
                str++;
            }
            else if (*str == '<' && *(str + 1) == '<')
            {
                arr[i++] = ft_strdup("<<");
                str++;
            }
            else
                arr[i++] = ft_strndup(str, 1);
            str++;
        }
        else if (*str && ft_isspace(*str))
            str++;
    }
    arr[i] = NULL;
    return (arr);
}