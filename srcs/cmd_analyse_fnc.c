/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_analyse_fnc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:56:14 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/24 18:26:52 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_new_arg_array(int pos_arg)
{
	int	i;
	int	size;

	i = 0;
	while (data.cur_cmd[pos_arg + i] && ft_strcmp(data.cur_cmd[pos_arg + i], "|"))
		i++;
	//printf("Args list start at %d size of %d\n", pos_arg, i);
	data.cur_args = malloc(sizeof(char*) * (i + 1));
	if (!data.cur_args)
		return (-1);
	size = i;
	while (i >= 0)
	{
		data.cur_args[i] = NULL;
		i--;
	}
	return (size);
}

int ft_check_arrows(char *str)
{
    if (ft_strcmp(str, "<") == 0 
        || ft_strcmp(str, ">") == 0)
        return (1);
    else
        return (0);
}

int	ft_add_arg_to_cur_args(char *arg)
{
	int	i;

	i = 0;
	while (data.cur_args[i])
		i++;
	data.cur_args[i] = ft_strdup(arg);
	//printf("[%d] %s\n", i, data.cur_args[i]);
	return (0);
}

// < in.txt grep a | wc -l > out.txt
// 

int	cmd_line_analyser(int id_cmd)
{
	int	i;
	int	size_cmd;

	data.cur_cmd = ft_split_spaces(data.cmd[id_cmd]);
	data.cur_cmd = replace_dollar_args(data.cur_cmd);
	//prt_args(data.cur_cmd);
	//printf("\n");
	
	i = -1;
	size_cmd = 0;
	while (data.cur_cmd[++i])
	{
		if (!size_cmd)
			size_cmd = ft_new_arg_array(i);
		if (ft_check_arrows(data.cur_cmd[i]))
		{
			ft_do_redir(data.cur_cmd[i], data.cur_cmd[i + 1]);
			i ++;
			continue;
		}
		if  (!ft_strcmp(data.cur_cmd[i], "|"))
		{
			// call execve with pipe
			ft_cmd_laucher_main(1);
			//prt_array(data.cur_args);
			//printf("\n");
			size_cmd = 0;
			continue;
		}
		ft_add_arg_to_cur_args(data.cur_cmd[i]);
	}
	// call execve without pipe
	if (ft_cmd_laucher_main(0))
		printf("msh: command not found: %s\n", data.cur_args[0]);
	//prt_array(data.cur_args);
	return (0);
}

// < in.txt grep a | wc -l > out.txt
