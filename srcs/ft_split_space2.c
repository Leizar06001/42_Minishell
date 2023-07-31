/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:47:23 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/31 17:52:14 by raphaellous      ###   ########.fr       */
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
