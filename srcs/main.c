/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/08/03 13:10:29 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	g_data;

static void	init_signals_handlers(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_int);
}

static int	ft_check_synthax_and_parse(void)
{
	int	err;

	quote_error(g_data.cmd);
	err = two_pipes_with_space(g_data.cmd);
	if (err)
		return (err);
	err = is_last_char_pipe(g_data.cmd);
	if (err)
		return (err);
	g_data.cur_cmd = ft_parse(g_data.cmd, 0);
	replace_dollar_args(g_data.cur_cmd);
	return (0);
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
		if (!str_only_space_tab(g_data.cmd))
		{
			add_history(g_data.cmd);
			err = ft_check_synthax_and_parse();
			if (!err)
				err = init_cmd_line_analyser();
			if (err == ERR_EXEC)
				ft_reset_redirs();
			if (!err || err)
			{
				free_2d(g_data.cur_cmd);
				g_data.cur_args = NULL;
			}
		}
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

// simple quote ferme les double
// wildcard
