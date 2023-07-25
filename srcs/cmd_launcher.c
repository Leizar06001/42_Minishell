/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_launcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:33:42 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/25 14:47:25 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtin_fnc(char **cmd)
{
	char	s[255];

	if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "chdir"))
		ft_chdir(cmd[1]);
	else if (!ft_strcmp(cmd[0], "pwd"))
		printf("%s\n", getcwd(s, 255));
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
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

int	ft_cmd_laucher_main(int has_pipe)
{
	int	err;

	err = ft_builtin_fnc(g_data.cur_args);
	if (err == -1)
		err = ft_execve_launcher(has_pipe);
	if (has_pipe)
		ft_reset_files_redir();
	else
		ft_reset_redirs();
	return (err);
}
