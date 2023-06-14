/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/14 15:21:00 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data data;

void	exex_echo(const char *arg)
{
    char *args[] = {"echo", (char *)arg, "qwe", "nbvcx", NULL};
	
    execve(data.path_fnc, args, NULL);
}

int	exec_cmd(int id_cmd)
{
	char	**cmd_line;
	char	s[100];

	cmd_line = ft_split_spaces(data.cmd[id_cmd]);
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
		return (1);
	else
		printf("shell: command not found: %s\n", cmd_line[0]);
	return (0);
}

int	main(int i, char *argv[], char **env)
{	
	(void)argv;
	
	init_struct(env);
	signal(SIGQUIT, handler_quit);
	signal(SIGINT, handler_int);
	rl_catch_signals = 0;

	while (!data.exit)
	{
		data.line = readline(data.minishell_name);
		quote_error(data.line);
		data.cmd = ft_split(data.line, ';');
		i = -1;
		while (data.cmd[++i] && !data.exit)
		{
			add_history(data.cmd[i]);
			data.exit = exec_cmd(i);
		}
	}
	return (0);
	free_struct();
}
 