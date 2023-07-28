/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:54:39 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/28 19:03:10 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	c;
	size_t	i;

	str = &c;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < len && s[i] && start < ft_strlen(s))
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_nb_words(char const *s, char c)
{
	int	i;
	int	nb_words;
	int	next_word;

	nb_words = 0;
	next_word = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && next_word)
		{
			nb_words++;
			next_word = 0;
		}
		if (s[i] == c)
			next_word = 1;
		i++;
	}
	return (nb_words);
}

static int	ft_len_word(char const *s, char c, int start)
{
	int	len;

	len = 0;
	while (s[start + len] && s[start + len] != c)
		len++;
	return (len);
}

static char	**ft_free_all(char **tb, int tb_size)
{
	int	i;

	i = 0;
	while (i < tb_size)
	{
		free(tb[i]);
		i++;
	}
	free(tb);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		pos_word;
	int		nb_words;
	int		len_word;
	char	**tb;

	nb_words = ft_nb_words(s, c);
	tb = malloc(sizeof(char *) * (1 + nb_words));
	if (!tb)
		return (0);
	pos_word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		len_word = ft_len_word(s, c, i);
		if (len_word > 0)
			tb[pos_word++] = ft_substr(s, i, len_word);
		if (!tb[pos_word - 1])
			return (ft_free_all(tb, pos_word - 1));
		i = i + len_word;
	}
	tb[pos_word] = NULL;
	return (tb);
}
