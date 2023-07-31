/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FT_SPLIT_SPACE3.C                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:51:15 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/31 17:54:34 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	joinquote(char **arr, int i, char c)
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
	if (*(str - 1) == '"')
		g_data.prev_is_dquote = 1;
	else if (*(str - 1) == '\'')
		g_data.prev_is_quote = 1;
	else
		g_data.prev_is_quote = 0;
	arr[i++] = malloc_word(str);
	while (*str && !ft_isspace(*str) && *str != '\"' && *str != '>'
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
