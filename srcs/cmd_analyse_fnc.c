/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_analyse_fnc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:56:14 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/14 18:00:02 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_check_arrows(char *str)
{
    if (ft_strcmp(str, "<") == 0 
        || ft_strcmp(str, ">") == 0)
        return (1);
    else
        return (0);
}

void    ft_rm_redir_from_args(int line)
{
    int i;
    int j;
    char    **ret;

    i = -1;
    j = 0;
    ret = malloc(sizeof(char *) * (ft_size_array(data.cur_args[line]) + 1));
    while (data.cur_args[line][++i])
    {
        if (ft_check_arrows(data.cur_args[line][i]))
            i += 2;
        ret[j] = ft_strdup(data.cur_args[line][i]);
        j++;
    }
    ret[j] = NULL;
    free_2d(data.cur_args[line]);
    data.cur_args[line] = ret;
}

int	check_redir(int line)
{
	int	i;
	int	err;

	i = -1;
	err = 0;
	while (data.cur_args[line][++i])
	{
		if (ft_strcmp(data.cur_args[line][i], "<") == 0)
		{
			//err = ft_redir_input(data.cur_args[line][i + 1]);
			printf("Input redir to %s\n", data.cur_args[line][i + 1]);
			if (err)
				return (1);
		}
		if (ft_strcmp(data.cur_args[line][i], ">") == 0)
		{
			//err = ft_redir_output(data.cur_args[line][i + 1]);
			printf("Output redir to %s\n", data.cur_args[line][i + 1]);
			if (err)
				return (1);
		}
	}
    ft_rm_redir_from_args(line);
	return (0);
}

int ft_fill_arg_line(int line, int start, int end)
{
	int	i;

	//printf("Fill line %d, %d - %d\n", line, start, end);
	i = 0;
	while (start <= end)
	{
		data.cur_args[line][i] = ft_strdup(data.cur_cmd[start]);
		start++;
		i++;
	}
	//data.cur_args[line][i] = NULL;
	//printf("Done filling\n");
	return (0);
}

int	ft_malloc_arg_array()
{
	int start = 0;

	int i = -1;
	int p = 0;

	//printf("malloc array\n");
	while (data.cur_cmd[++i])
	{
		start = i;
		while (data.cur_cmd[i] && ft_strcmp(data.cur_cmd[i], "|"))
			i++;
		data.cur_args[p] = (char **) malloc(sizeof(char *) * (i - start + 1));
		if (!data.cur_args[p])
			return (-1);
		ft_fill_arg_line(p, start, i - 1);
		p++;
		//printf("next i : %d\n", i);
		if (!data.cur_cmd[i])
			break;
	}
	//printf("last p : %d\n", p);
	data.cur_args[p] = NULL;
	//printf("Done malloc\n");
	return (0);
}

int	ft_split_pipes()
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (data.cur_cmd[++i])
	{
		if (ft_strcmp(data.cur_cmd[i], "|") == 0)
			j++;
	}
	data.cur_args = (char ***) malloc(sizeof(char **) * (j + 2));
	if (!data.cur_args)
		return (-1);
	ft_malloc_arg_array();
	return (j);
}


