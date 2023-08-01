/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:51:31 by raphaellous       #+#    #+#             */
/*   Updated: 2023/08/01 17:52:57 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	ft_isthan(char c)
{
	return (c == '>' || c == '<');
}

int	ft_is2quote(char c)
{
	return (c == '\'' || c == '\"');
}

char	*ft_strndup(char *str, int n)
{
	char	*new;
	int		i;

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

char	*malloc_word(char *str)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[len] && !ft_isspace(str[len]) && !ft_is2quote(str[len]) && !ft_isthan(str[len]) && str[len] != '|')
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i] && !ft_isspace(str[i]) && !ft_is2quote(str[i]) && !ft_isthan(str[i]) && str[i] != '|')
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	if (str[i] == '\"')
		g_data.next_is_dquote = 1;
	if (str[i] == '\'')
		g_data.next_is_quote = 1;
	return (word);
}

char	*char_parse(char **arr, char *str, int *i)
{
	arr[*i] = malloc_word(str);
	*i += 1;
	while (*str && !ft_isspace(*str) && !ft_is2quote(*str) && !ft_isthan(*str) && *str != '|')
		str++;
	if (g_data.prev_is_dquote == 1 || g_data.prev_is_quote == 1)
	{
		if (g_data.prev_is_dquote == 1)
			arr[*i - 2] = remove_dquote(arr[*i - 2], '\"');
		else
			arr[*i - 2] = remove_dquote(arr[*i - 2], '\'');
		arr[*i - 2] = ft_strjoin(arr[*i - 2], arr[*i - 1]);
		arr[*i - 1] = NULL;
		*i -= 1;
		g_data.prev_is_dquote = 0;
		g_data.prev_is_quote = 0;
	}
	return (str);
}

char	*morethan_parse(char **arr, char *str, int *i)
{
	if (*str == '>' && *(str + 1) == '>')
	{
		arr[*i] = ft_strdup(">>");
		str++;
	}
	else if (*str == '<' && *(str + 1) == '<')
	{
		arr[*i] = ft_strdup("<<");
		str++;
	}
	else
		arr[*i] = ft_strndup(str, 1);
	*i += 1;
	str++;
	return (str);
}

char	*pipe_parse(char **arr, char *str, int *i)
{
	if (*str == '|')
	{
		arr[*i] = ft_strdup("|");
		*i += 1;
		str++;
	}
	return (str);
}

char	*malloc_word_dquote(char *str, int i, int len)
{
	char	*word;

	if (str[len] == '\"')
		len++;
	while (str[len] && str[len] != '\"')
		len++;
	if (str[len] == '\"')
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (++i < len)
	{
		word[i] = str[i];
	}
	word[i] = '\0';
	return (word);
}

char	*pass_word(char *str, char c)
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
			break ;
		}
	}
	return (str);
}

char	*remove_dquote(char *str, char c)
{
	int		longueur;
	int		i;
	char	*new;

	i = 0;
	longueur = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * (longueur - 1));
	if (longueur >= 2 && str[0] == c && str[longueur - 1] == c)
	{
		while (i < longueur - 2)
		{
			new[i] = str[i + 1];
			i++;
		}
		new[i] = '\0';
	}
	else
		return (str);
	return (new);
}

void	joinquote(char **arr, int *i, char c)
{
	arr[*i - 1] = remove_dquote(arr[*i - 1], c);
	if (g_data.next_is_quote == 1 || g_data.next_is_dquote == 1)
	{
		arr[*i - 2] = ft_strjoin(arr[*i - 2], arr[*i - 1]);
		arr[*i - 1] = NULL;
		*i -= 1;
		g_data.next_is_quote = 0;
	}
}

char	*dquote_parse(char **arr, char *str, int *i)
{
	arr[*i] = malloc_word_dquote(str, -1, 0);
	*i += 1;
	str = pass_word(str, '\"');
	joinquote(arr, i, '"');
	if (*str == '\"' || *str == '\'')
		g_data.next_is_quote = 1;
	if (*str && !ft_isspace(*str) && !ft_isthan(*str) && *str != '|')
		g_data.prev_is_dquote = 1;
	return (str);
}

char	*malloc_word_quote(char *str, int i, int len)
{
	char	*word;

	if (str[len] == '\'')
		len++;
	while (str[len] && str[len] != '\'')
		len++;
	if (str[len] == '\'')
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (++i < len)
	{
		word[i] = str[i];
	}
	word[i] = '\0';
	return (word);
}

char	*quote_parse(char **arr, char *str, int *i)
{
	arr[*i] = malloc_word_quote(str, -1, 0);
	*i += 1;
	str = pass_word(str, '\'');
	joinquote(arr, i, '\'');
	if (*str == '\"' || *str == '\'')
		g_data.next_is_quote = 1;
	if (*str && !ft_isspace(*str) && !ft_isthan(*str) && *str != '|')
		g_data.prev_is_dquote = 1;
	return (str);
}

char	**ft_parse(char *str, int i)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (1000));
	i = 0;
	if (!arr)
		return (NULL);
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && *str == '"')
			str = dquote_parse(arr, str, &i);
		else if (*str && *str == '\'')
			str = quote_parse(arr, str, &i);
		else if (*str && !ft_isspace(*str) && !ft_isthan(*str) && *str != '|')
			str = char_parse(arr, str, &i);
		else if (*str && (*str == '>' || *str == '<'))
			str = morethan_parse(arr, str, &i);
		else if (*str && *str == '|')
			str = pipe_parse(arr, str, &i);
	}
	arr[i] = NULL;
	return (arr);
}
