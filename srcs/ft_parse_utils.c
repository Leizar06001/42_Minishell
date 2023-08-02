/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 08:26:40 by raphaellous       #+#    #+#             */
/*   Updated: 2023/08/02 08:28:42 by raphaellous      ###   ########.fr       */
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
