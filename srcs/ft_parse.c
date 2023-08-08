/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/08/08 17:36:42 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_dquote(char *str, char c)
{
	int		longueur;
	int		i;
	char	*new;

	i = 0;
	longueur = ft_strlen(str);
	if (longueur <= 1)
		return(ft_strdup(""));
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
	{
		free(new);
		return (str);
	}
	return (new);
}

void	joinquote(char **arr, int *i, char c)
{
	char	*tmp;
	//char	*tmp2;

	(void)c;
	tmp = remove_dquote(arr[*i - 1], c);
	//free(arr[*i - 1]);
	arr[*i - 1] = tmp;
	if (g_data.next_is_quote == 1 || g_data.next_is_dquote == 1)
	{
		//tmp2 = arr[*i - 2];
		//tmp = arr[*i - 1];
		arr[*i - 2] = ft_strjoin(arr[*i - 2], arr[*i - 1]);
		//free(tmp);
		//free(tmp2);
		arr[*i - 1] = NULL;
		*i -= 1;
		g_data.next_is_quote = 0;
		g_data.next_is_dquote = 0;
	}
}

static void	init_parse(void)
{
	g_data.next_is_quote = 0;
	g_data.next_is_dquote = 0;
	g_data.prev_is_quote = 0;
	g_data.prev_is_dquote = 0;
}

char	**ft_parse(char *str, int i)
{
	char	**arr;

	init_parse();
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
