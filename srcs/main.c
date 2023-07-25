/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/07/25 17:37:21 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	g_data;

static void	init_signals_handlers(void)
{
	signal(SIGQUIT, handler_quit);
	signal(SIGINT, handler_int);
}

static int	ft_read_command_loop(void)
{
	int	i;

	rl_catch_signals = 0;
	while (!g_data.exit)
	{
		g_data.line = readline(g_data.minishell_name);
		if (g_data.line == NULL)
			clean_exit();
		//quote_error(g_data.line);
		add_history(g_data.line);
		g_data.cmd = ft_split(g_data.line, ';');
		i = -1;
		while (g_data.cmd[++i] && !g_data.exit)
		{
			g_data.cur_cmd = ft_split_spaces(g_data.cmd[i]);
			g_data.cur_cmd = replace_dollar_args(g_data.cur_cmd);
			cmd_line_analyser();
		}
		//free_2d(g_data.cmd);
		free(g_data.line);
	}
	return (0);
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

// < in.txt grep a | wc -l > out.txt
// ls > out.txt | wc -l

/* ******* TO DO **********
FREEEEEEEs
Ctrl c
!pwd dans dossier supprime

<<
!Pipe fin de ligne
!Rien entre 2 pipes
Execve prioritaire sur builtin
Supprimer path de data



Shell level
Echo avec un seul "
Export sans arg


*/
