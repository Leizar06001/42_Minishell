/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/07/31 15:45:03 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	g_data;

 void enable_raw_mode() {
    tcgetattr(0, &(g_data.orig_termios));
    g_data.raw_termios = g_data.orig_termios;
    //g_data.raw_termios.c_lflag &= ~();
    tcsetattr(0, TCSANOW, &(g_data.raw_termios));
}

 void disable_raw_mode() {
    tcsetattr(0, TCSANOW, &(g_data.orig_termios));
}

static void	init_signals_handlers(void)
{
	signal(SIGQUIT, handler_quit);
	signal(SIGINT, handler_int);
}

// static int	ft_read_command_loop(void)
// {
// 	int	i;

// 	while (!g_data.exit)
// 	{
// 		g_data.line = readline(g_data.minishell_name);
// 		if (g_data.line == NULL)
// 			break ;
// 		add_history(g_data.line);
// 		g_data.cmd = ft_split(g_data.line, ';');
// 		i = -1;
// 		while (g_data.cmd[++i] && !g_data.exit)
// 		{
// 			g_data.cur_cmd = ft_split_spaces(g_data.cmd[i]);
// 			g_data.cur_cmd = replace_dollar_args(g_data.cur_cmd);

// 			cmd_line_analyser();
// 		}
// 		free_2d(g_data.cmd);
// 		free(g_data.line);
// 	}
// 	return (0);
// }

static void	ft_read_command_loop(void)
{
	int	err;

	while (!g_data.exit)
	{
		err = 0;
		g_data.cmd = readline(g_data.minishell_name);
		if (g_data.cmd == NULL)
			break ;
		add_history(g_data.cmd);
		g_data.cur_cmd = ft_split_spaces(g_data.cmd);
		g_data.cur_cmd = replace_dollar_args(g_data.cur_cmd);
		err = quote_error(g_data.cmd);
		if (!err)
			err = two_pipes_with_space(g_data.cmd);
		if (!err)
			err = is_last_char_pipe(g_data.cmd);
		if (!err)
		{
			if (cmd_line_analyser() == -1)
				ft_reset_redirs();
		}
		free(g_data.cmd);
	}
}

int	main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	init_struct(env);
	enable_raw_mode();
	init_signals_handlers();
	ft_read_command_loop();
	printf("exit\n");
	disable_raw_mode();
	clean_exit();
	return (0);
}

/* ******* TO DO **********
FREEEEEEEs
Ctrl \ > should not do anything || termios ?


!Pipe fin de ligne
!Rien entre 2 pipes
Echo avec un seul "


*/
