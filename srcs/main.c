/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/07/24 19:00:46 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data data;

void	init_signals_handlers()
{
	signal(SIGQUIT, handler_quit);
	signal(SIGINT, handler_int);
}

int	ft_read_command_loop()
{
	int	i;

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
		}
		//free_2d(data.cmd);
		free(data.line);
	}
}

int	main(int argc, char *argv[], char **env)
{	
	(void)argc;
	(void)argv;
	
	init_struct(env);
	init_signals_handlers();
	ft_read_command_loop();
	clean_exit();
	return (0);
}

/* ******* TO DO **********
FREEEEEEEs

< in.txt grep a | wc -l > out.txt
*/
