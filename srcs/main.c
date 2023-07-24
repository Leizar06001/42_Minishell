/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/07/24 18:22:06 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data data;

// int	exec_cmd(int id_cmd)
// {
// 	char	**cmd_line;
	
// 	cmd_line = ft_split_spaces(data.cmd[id_cmd]);
// 	cmd_line = replace_dollar_args(cmd_line);
// 	prt_args(cmd_line);
// 	if (cmd_line[0] == NULL)
// 		return (0);
// 	if (ft_builtin_fnc(cmd_line))
// 	{
// 		select_output(cmd_line);
// 		return (0);
// 	}
// 	else if (!ft_strcmp(cmd_line[0], "exit"))
// 		return (1);
// 	else
// 	{
// 		if (ft_execve(cmd_line))
// 			printf("shell: command not found: %s\n", cmd_line[0]);
// 	}
// 	select_output(cmd_line);
// 	return (0);
// }

int	main(int i, char *argv[], char **env)
{	
	(void)i;
	(void)argv;
	
	init_struct(env);
	signal(SIGQUIT, handler_quit);
	signal(SIGINT, handler_int);
	//rl_catch_signals = 0;

	data.orig_fd_in = dup(STDIN_FILENO);

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

< in.txt grep a | wc -l > out.txt
*/
