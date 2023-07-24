/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:09 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/24 19:37:42 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int         ft_isspace(char c)
{
    return (c == ' ' || c == '\n' || c == '\t');
}

int ft_isthan(char c)
{
    return (c == '>' || c == '<');
}

char    *remove_dquote(char* str, char c)
{
    int longueur = ft_strlen(str);
    int i;
    char *new;

    i = 0;
    new = (char *)malloc(sizeof(char) * (longueur - 1));
    if (longueur >= 2 && str[0] == c && str[longueur - 1] == c)
    {
        while(i < longueur - 2)
        {
            new[i] = str[i + 1];
            i++;
        }
        new[i] = '\0';
    }
    else
        return(str);
    return (new);
}

// {
//     int longueur = ft_strlen(str);
//     int i;
//     char *new;

//     i = 0;
//     new = (char *)malloc(sizeof(char) * (longueur - 1));
//     if (longueur >= 2 && str[0] == '"' && str[longueur - 1] == '"')
//     {
//         while(i < longueur - 2)
//         {
//             new[i] = str[i + 1];
//             i++;
//         }
//         new[i] = '\0';
//     }
// 	else
// 		return(str);
//     return (new);
// }

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
    while(str[len] && !ft_isspace(str[len]) && str[len] != '\"' && str[len] != '>' && str[len] != '<' && str[len] != '|')
            len++;
    word = (char *)malloc(sizeof(char) * (len + 1));
    while (str[i] && !ft_isspace(str[i]) && str[i] != '\"' && str[i] != '>' && str[i] != '<' && str[i] != '|')
    {
            word[i] = str[i];
            i++;
    }
    if (str[i] == '\"')
        g_data.next_is_quote = 1;
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
    {if(*(str - 1) == '"')
        g_data.prev_is_dquote = 1;
    else if (*(str - 1) == '\'')
        g_data.prev_is_quote = 1;
    else
        g_data.prev_is_quote = 0;
            word[i] = str[i];
            i++;
    }
    if (str[i - 1] == '\"' || str[i - 1] == '\'')
        g_data.prev_is_quote = 1;

    word[i] = '\0';
    return (word);
}

char    *malloc_word_quote3(char *str)
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
    while (/*str[i] && str[i] != '\"'*/ i < len)
    {if(*(str - 1) == '\"')
        g_data.prev_is_dquote = 1;
    else if (*(str - 1) == '\'')
        g_data.prev_is_quote = 1;
    else
        g_data.prev_is_quote = 0;
            word[i] = str[i];
            i++;
    }
    if (str[i - 1] == '\"' || str[i - 1] == '\'')
        g_data.prev_is_quote = 1;

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
    if (str[i - 1] == '\'')
        g_data.prev_is_quote = 1;
    word[i] = '\0';
    return (word);
}

//fonction qui va passer le mot qui est entre guillemets

char    *pass_word(char *str, char c)
{
while (*str)
{
    if (*str == c)
        str++;
    while (*str != c && *str)
        str++;
    if (*str == c)
    {
        str++;
        break;
    }
}
    return (str);
}

char    *morethan(char **arr, char *str, int i)
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
            g_data.i_splitspaces = i;
            return (str);
}

char    *pipe_split(char **arr, char *str, int i)
{
    if (*str == '|')
            {
                arr[i++] = ft_strdup("|");
                str++;
            }
            g_data.i_splitspaces = i;
            return (str);
}

char *just_character(char **arr, char *str, int i)
{
    if(*(str - 1) == '"')
        g_data.prev_is_dquote = 1;
    else if (*(str - 1) == '\'')
        g_data.prev_is_quote = 1;
    else
        g_data.prev_is_quote = 0;
    arr[i++] = malloc_word(str);
    while (*str && !ft_isspace(*str) && *str != '\"' && *str != '>' && *str != '<' &&*str != '|')
        str++;
    if (g_data.prev_is_dquote == 1 || g_data.prev_is_quote == 1)
    {
        if (g_data.prev_is_dquote == 1)
            arr[i - 2] = remove_dquote(arr[i - 2], '\"');
        else
            arr[i - 2] = remove_dquote(arr[i - 2], '\'');
        arr[i - 2] = ft_strjoin(arr[i - 2], arr[i - 1]);
        i--;
        g_data.prev_is_dquote = 0;
        g_data.prev_is_quote = 0;
    }
    g_data.i_splitspaces = i;
    return (str);
}

void joinquote(char **arr, int i, char c)
{
    if (g_data.next_is_quote == 1)
    {
        arr[i - 1] = remove_dquote(arr[i - 1], c);
        arr[i - 2] = ft_strjoin(arr[i - 2], arr[i - 1]);
        i--;
        g_data.next_is_quote = 0;
    }
    g_data.i_splitspaces = i;
}

char    **ft_split_spaces(char *str)
{
    char    **arr;
    int     i;

    i = 0;
    arr = (char **)malloc(sizeof(char *) * (count_words(str) + 10));
    if (!arr)
        return (NULL);
    while (*str)
    {
        while (*str && ft_isspace(*str))
            str++;
        if (*str && *str == '"')
        {
            arr[i++] = malloc_word_quote(str);
            str = pass_word(str, '\"');
            joinquote(arr, i, '"');
        }
        else if (*str && *str == '\'')
        {
            arr[i++] = malloc_word_quote3(str);
            str = pass_word(str, '\'');
            joinquote(arr, i, '\'');
        }
        else if (*str && !ft_isspace(*str) && *str != '>' && *str != '<' && *str != '|')
            str = just_character(arr, str, i);
        else if (*str && (*str == '>' || *str == '<'))
            str = morethan(arr, str, i);
        else if (*str && *str == '|')
            str = pipe_split(arr, str, i);
        i = g_data.i_splitspaces;
    }
    arr[i] = NULL;
    return (arr);
}
