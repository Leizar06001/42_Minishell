/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:51:15 by raphaellous       #+#    #+#             */
/*   Updated: 2023/08/01 14:55:40 by mabdali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	joinquote(char **arr, int i, char c)
{
	if (g_data.next_is_quote == 1)
	{
		arr[i - 1] = remove_dquote(arr[i - 1], c);
		arr[i - 2] = ft_strjoin(arr[i - 2], arr[i - 1]);
		arr[i - 1] = NULL;
		i--;
		g_data.next_is_quote = 0;
	}
	g_data.i_splitspaces = i;
}

char	*pipe_split(char **arr, char *str, int i)
{
	if (*str == '|')
	{
		arr[i++] = ft_strdup("|");
		str++;
	}
	g_data.i_splitspaces = i;
	return (str);
}

char	*morethan(char **arr, char *str, int i)
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

char	*just_character(char **arr, char *str, int i)
{
	if(g_data.strsplit != str)
	{
		if (*(str - 1) == '"')
			g_data.prev_is_dquote = 1;
		else if (*(str - 1) == '\'')
		g_data.prev_is_quote = 1;
		else
		g_data.prev_is_quote = 0;
	}
	else
		g_data.prev_is_quote = 0;
	arr[i++] = malloc_word(str);
	while (*str && !ft_isspace(*str) && *str != '\"' && *str != '\'' && *str != '>'
		&& *str != '<' && *str != '|')
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

char	*malloc_word(char *str)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[len] && !ft_isspace(str[len]) && str[len] != '\"' && str[len] != '\''
		&& str[len] != '>' && str[len] != '<' && str[len] != '|')
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i] && !ft_isspace(str[i]) && str[i] != '\"' && str[i] != '\'' && str[i] != '>'
		&& str[i] != '<' && str[i] != '|')
	{
		word[i] = str[i];
		i++;
	}
	if (str[i] == '\"' || str[i] == '\'')
		g_data.next_is_quote = 1;
	word[i] = '\0';
	return (word);
}
