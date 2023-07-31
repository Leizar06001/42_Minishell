/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:01:01 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/31 15:15:08 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int checkquoteclosed	(char* str)
{
	int	error = 0;

	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while(*str != '\'' && *str)
				str++;
			if(*str == '\0')
				error = 1;
			else
			{
				str++;
				error = 0;
			}
		}

		else if(*str == '\"')
		{
			str++;
			while(*str != '\"' && *str)
				str++;
			if(*str == '\0')
				error = 2;
			else
			{
				str++;
				error = 0;
			}
		}
		else
			str++;
	}
	return (error);
}

int quote_error(char *str)
{
	char	*tmp;

	while (checkquoteclosed(str) != 0)
	{
		if(checkquoteclosed(str) == 1)
			tmp = readline("quote> ");
		if(checkquoteclosed(str) == 2)
			tmp = readline("dquote> ");
		g_data.cmd = ft_strjoin(g_data.cmd, tmp);
		if (ft_strcmp(tmp, "\"") != 0)
			g_data.cmd = ft_strjoin(g_data.cmd, "\n");
		str = g_data.cmd;
	}
	return (0);
}

int pipe_is_last2(char *str)
{
	int i;
	int last_is_pipe;

	i = 0;
	last_is_pipe = 0;
	while(str[i])
	{
		if(str[i] == '|')
		{
			if (last_is_pipe == 0)
				last_is_pipe = 1;
			else if (last_is_pipe == 1)
				return(1);
			i++;
		}
		else if (str[i] == ' ')
			i++;
		else
		{
			if (last_is_pipe == 1)
				last_is_pipe = 0;
			i++;
		}
	}
	return (0);
}

int is_last_char_pipe(char *str)
{
	int len;
	int i;

	len = strlen(str);
	i = len - 1;
	if (len == 0)
		return 0;

	while (i >= 0 && str[i] == ' ')
		i--;
	if (i >= 0 && str[i] == '|')
	{
		printf("msh: error: expected expression after pipe\n");
		return 1;
	}
	return (0);
}


int two_pipes_with_space(char *str)
{
	int i;
	int pipe_count;
	int space_between_pipes;

	i = 0;
	pipe_count = 0;
	space_between_pipes = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			pipe_count++;
			if (pipe_count == 2 && space_between_pipes == 1)
			{
				printf("msh: error: two consecutive pipes\n");
				return 1; // Deux '|' se suivent avec des espaces entre eux
			}
			if (pipe_count == 2)
			{
				printf("msh: error: two consecutive pipes (||)\n");
				return 1;
			}
			space_between_pipes = 0;
		}
		else if (str[i] == ' ')
			space_between_pipes = 1;
		else
		{
			pipe_count = 0;
			space_between_pipes = 0;
		}
		i++;
	}
	return 0; // Aucun cas de deux '|' se suivant avec des espaces entre eux
}
