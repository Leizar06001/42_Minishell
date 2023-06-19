/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/19 16:52:18 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data data;

void	prt_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		printf("(arg[%d]:%s)\n", i, args[i]);
		i++;
	}
}

int	builtin_fnc(char **cmd)
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
	else
		return (0);
	return (1);
}

int	exec_cmd(int id_cmd)
{
	char	**cmd_line;
	
	cmd_line = ft_split_spaces(data.cmd[id_cmd]);
	cmd_line = replace_dollar_args(cmd_line);
	//prt_args(cmd_line);
	if (cmd_line[0] == NULL)
		return (0);
	if (builtin_fnc(cmd_line))
	{
		select_output(cmd_line);
		return (0);
	}
	else if (!ft_strcmp(cmd_line[0], "exit"))
		return (1);
	else
	{
		if (ft_execve(cmd_line))
			printf("shell: command not found: %s\n", cmd_line[0]);
	}
	select_output(cmd_line);
	return (0);
}

int	main(int i, char *argv[], char **env)
{	
	(void)i;
	(void)argv;
	
	init_struct(env);
	signal(SIGQUIT, handler_quit);
	signal(SIGINT, handler_int);
	rl_catch_signals = 0;

	while (!data.exit)
	{
		data.line = readline(data.minishell_name);
		if (data.line == NULL)
			clean_exit();
		//quote_error(data.line);
		data.cmd = ft_split(data.line, ';');
		i = -1;
		while (data.cmd[++i] && !data.exit)
		{
			add_history(data.cmd[i]);
			data.exit = exec_cmd(i);
		}
		//free_2d(data.cmd);
		free(data.line);
	}
	clean_exit();
	return (0);
}

/* ******* TO DO **********
CTRL + D ne fonctionne pas si la ligne n'est pas vide


FREEEEEEEs
*/
