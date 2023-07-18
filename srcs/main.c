/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/07/14 18:00:41 by raphaellous      ###   ########.fr       */
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
	prt_args(cmd_line);
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

void	prt_arg_array()
{
	int	i;
	int	j;

	printf("----- ARGS ARRAY -----\n");
	i = -1;
	while (data.cur_args[++i])
	{
		j = -1;
		while (data.cur_args[i][++j])
			printf("%s, ", data.cur_args[i][j]);
		printf("\n");
	}
	printf("-----------------------\n");
}

int	cmd_line_analyser(int id_cmd)
{
	int	i;

	data.cur_cmd = ft_split_spaces(data.cmd[id_cmd]);
	data.cur_cmd = replace_dollar_args(data.cur_cmd);
	prt_args(data.cur_cmd);

	ft_split_pipes();
	prt_arg_array();

	i = -1;
	while (data.cur_args[++i])
	{
		printf(" > Arg line #%d\n", i);
		check_redir(i);
		// if (data.cur_args[i + 1])
		// 	ft_call_execve(data.cur_args[i], i, 1);
		// else
		// 	ft_call_execve(data.cur_args[i], i, 0);
	}
	prt_arg_array();
	return (0);
}

int	main(int i, char *argv[], char **env)
{	
	(void)i;
	(void)argv;
	
	init_struct(env);
	signal(SIGQUIT, handler_quit);
	signal(SIGINT, handler_int);
	//rl_catch_signals = 0;

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
			data.exit = cmd_line_analyser(i);
			//data.exit = exec_cmd(i);
		}
		//free_2d(data.cmd);
		free(data.line);
	}
	clean_exit();
	return (0);
}

/* ******* TO DO **********
PIPPEX
FREEEEEEEs
*/
