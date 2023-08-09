/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:01:01 by rloussig          #+#    #+#             */
/*   Updated: 2023/08/09 14:19:32 by rloussig         ###   ########.fr       */
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
	while (checkquoteclosed(str) != 0)
	{
		if (checkquoteclosed(str) == 1)
			printf("msh: synthax error: quote\n");
		if (checkquoteclosed(str) == 2)
			printf("msh: synthax error: dquote\n");
		return (-1);
	}
	return (0);
}
