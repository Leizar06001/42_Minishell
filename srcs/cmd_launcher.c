/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_launcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:33:42 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/31 15:26:39 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_builtin_fnc(char **cmd)
{
	if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd, 0);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env();
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(g_data.cur_args[0], "exit"))
		g_data.exit = 1;
	else
		return (-1);
	return (0);
}

static int	ft_builtin_mandatory(char **cmd)
{
	if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "chdir"))
		ft_chdir(cmd[1]);
	else if (!ft_strcmp(cmd[0], "pwd"))
		printf("%s\n", ft_getvar("PWD"));
	else
		return (-1);
	return (0);
}

int	ft_cmd_laucher_main(int has_pipe)
{
	int	err;

	err = 0;
	if (g_data.cur_args)
	{
		if (g_data.cur_args[0])
		{
			err = ft_builtin_mandatory(g_data.cur_args);
			if (err == -1)
				err = ft_execve_launcher(has_pipe);
			if (err == 2)
				err = ft_builtin_fnc(g_data.cur_args);
		}
	}
	if (has_pipe)
		ft_reset_files_redir();
	else
		ft_reset_redirs();
	if (g_data.heredoc)
	{
		unlink(g_data.heredoc);
		free(g_data.heredoc);
		g_data.heredoc = NULL;
	}
	return (err);
}
