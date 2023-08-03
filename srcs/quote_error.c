/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:01:01 by rloussig          #+#    #+#             */
/*   Updated: 2023/08/02 15:47:51 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*checkquotecl(int *error, char *str)
{
	if (str)
		str++;
	while (*str != '\'' && *str)
		str++;
	if (!*str)
		*error = 1;
	else
	{
		str++;
		*error = 0;
	}
	return (str);
}

static char	*checkdquotecl(int *error, char *str)
{
	if (str)
		str++;
	while (*str != '\"' && *str)
		str++;
	if (!*str)
		*error = 2;
	else
	{
		str++;
		*error = 0;
	}
	return (str);
}

int	checkquoteclosed(char *str)
{
	int	error;

	error = 0;
	while (*str)
	{
		if (*str == '\'')
			str = checkquotecl(&error, str);
		else if (*str == '\"')
			str = checkdquotecl(&error, str);
		else
			str++;
	}
	return (error);
}

int	quote_error(char *str)
{
	char	*tmp;

	while (checkquoteclosed(str) != 0)
	{
		if (checkquoteclosed(str) == 1)
			tmp = readline("quote> ");
		if (checkquoteclosed(str) == 2)
			tmp = readline("dquote> ");
		if (tmp == NULL)
			return (-1);
		g_data.cmd = ft_strjoin(g_data.cmd, tmp);
		if (ft_strcmp(tmp, "\"") != 0)
			g_data.cmd = ft_strjoin(g_data.cmd, "\n");
		//free(str);
		free(tmp);
	}
	return (0);
}
