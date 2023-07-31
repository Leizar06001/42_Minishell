/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/07/31 18:51:40 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	g_data;

static void	init_signals_handlers(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_int);
}

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
		g_data.cur_cmd = ft_split_spaces(g_data.cmd, 0);
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
		free_2d(g_data.cur_cmd);
		free(g_data.cmd);
	}
}

int	main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	init_struct(env);
	init_signals_handlers();
	ft_read_command_loop();
	printf("exit\n");
	clean_exit();
	return (0);
}

/* ******* TO DO **********
FREEEEEEEs

*/
