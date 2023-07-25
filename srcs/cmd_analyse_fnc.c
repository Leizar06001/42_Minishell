/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_analyse_fnc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:56:14 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/25 09:24:21 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_new_arg_array(int pos_arg)
{
	int	i;
	int	size;

	i = 0;
	while (g_data.cur_cmd[pos_arg + i]
		&& ft_strcmp(g_data.cur_cmd[pos_arg + i], "|"))
		i++;
	g_data.cur_args = malloc(sizeof(char *) * (i + 1));
	if (!g_data.cur_args)
		return (-1);
	size = i;
	while (i >= 0)
	{
		g_data.cur_args[i] = NULL;
		i--;
	}
	return (size);
}

int	ft_check_arrows(char *str)
{
	if (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0)
		return (1);
	else
		return (0);
}

int	ft_add_arg_to_cur_args(char *arg)
{
	int	i;

	i = 0;
	while (g_data.cur_args[i])
		i++;
	g_data.cur_args[i] = ft_strdup(arg);
	return (0);
}

int	cmd_line_analyser(void)
{
	int	i;
	int	size_cmd;

	i = -1;
	size_cmd = 0;
	while (g_data.cur_cmd[++i])
	{
		if (!size_cmd)
			size_cmd = ft_new_arg_array(i);
		if (ft_check_arrows(g_data.cur_cmd[i]))
		{
			ft_do_redir(g_data.cur_cmd[i], g_data.cur_cmd[i + 1]);
			i ++;
			continue ;
		}
		if (!ft_strcmp(g_data.cur_cmd[i], "|"))
		{
			if (ft_cmd_laucher_main(WITHPIPE) == -1)
			{
				printf("msh: command not found: %s\n", g_data.cur_args[0]);
				return (-1);
			}
			size_cmd = 0;
			continue ;
		}
		ft_add_arg_to_cur_args(g_data.cur_cmd[i]);
	}
	if (ft_cmd_laucher_main(NOPIPE) == -1)
		printf("msh: command not found: %s\n", g_data.cur_args[0]);
	return (0);
}

// < in.txt grep a | wc -l > out.txt
