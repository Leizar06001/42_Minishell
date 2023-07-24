/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/07/24 19:37:42 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_g_data g_data;

int	exec_cmd(int id_cmd)
{
	char	**cmd_line;
	char	s[100];

	cmd_line = parse(g_data.cmd[id_cmd]);

	//cmd_line = ft_split_spaces(g_data.cmd[id_cmd]);
	// cmd_line = ft_split(g_data.cmd[id_cmd], ' ');
	if (cmd_line[0] == NULL)
		return (0);
	if (!ft_strcmp(cmd_line[0], "cd") || !ft_strcmp(cmd_line[0], "chdir"))
		ft_chdir(cmd_line[1]);
	else if (!ft_strcmp(cmd_line[0], "pwd"))
		printf("%s\n", getcwd(s, 100));
	else if (!ft_strcmp(cmd_line[0], "echo"))
		ft_echo(cmd_line);
	else if (!ft_strcmp(cmd_line[0], "env"))
		ft_env();
	else if (!ft_strcmp(cmd_line[0], "export"))
		ft_export(cmd_line);
	else if (!ft_strcmp(cmd_line[0], "unset"))
		ft_unset(cmd_line);
	else if (!ft_strcmp(cmd_line[0], "exit"))
	{
		free_2d(cmd_line);
		return (1);
	}
	else if (ft_execve(cmd_line))
			printf("shell: command not found: %s\n", cmd_line[0]);
	free_2d(cmd_line);
	return (0);
}

int	main(int i, char *argv[], char **env)
{
	(void)argv;
	(void)i;

	init_struct(env);
	signal(SIGQUIT, handler_quit);
	signal(SIGINT, handler_int);
	rl_catch_signals = 0;

	while (!g_data.exit)
	{
		// CTRL + D ne fonctionne pas si la ligne n'est pas vide
		g_data.line = readline(g_data.minishell_name);
		if (g_data.line == NULL)
			clean_exit();
		quote_error(g_data.line);
		g_data.cmd = ft_split(g_data.line, ';');
		i = -1;
		while (g_data.cmd[++i] && !g_data.exit)
		{
			add_history(g_data.cmd[i]);
			g_data.exit = exec_cmd(i);
		}
		free_2d(g_data.cmd);
		free(g_data.line);
	}
	clean_exit();
	return (0);
}
