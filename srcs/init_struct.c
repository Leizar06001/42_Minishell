/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:03 by rloussig          #+#    #+#             */
/*   Updated: 2023/08/01 11:12:28 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

static void	get_env(char **env)
{
	g_data.env = ft_arraydup_plus_one(env);
	g_data.nb_env_var = ft_size_array(g_data.env);
	g_data.cwd = getenv("PWD");
	g_data.current_folder = NULL;
}

static void	create_env(void)
{
	g_data.cwd = "/";
	g_data.env = (char **)malloc(sizeof(char *) * 2);
	g_data.env[0] = ft_strdup("PWD=/");
	g_data.env[1] = NULL;
	g_data.nb_env_var = 1;
	g_data.current_folder = NULL;
}

static int	init_path_lst(void)
{
	g_data.path_lst = (char **)malloc(sizeof(char *) * 1);
	if (!g_data.path_lst)
		return (-1);
	g_data.path_lst[0] = NULL;
	return (0);
}

void	update_datas_from_env(void)
{
	if (g_data.user)
		free(g_data.user);
	g_data.user = ft_getvar("USER");
	g_data.path = ft_getvar("PATH");
	g_data.home = ft_getvar("HOME");
	if (!g_data.user)
		g_data.user = "no-env";
	g_data.user = ft_strjoin(BLUE, g_data.user);
	if (g_data.initialized)
		free_2d(g_data.path_lst);
	else
		free(g_data.path_lst);
	if (g_data.path)
		g_data.path_lst = ft_split(g_data.path, ':');
	else
		init_path_lst();
	update_shell_name();
}

void	init_struct(char **env)
{
	g_data.initialized = 0;
	g_data.env = NULL;
	g_data.main_env = env;
	g_data.exit = 0;
	g_data.user = NULL;
	g_data.minishell_name = NULL;
	g_data.output = NULL;
	init_path_lst();
	g_data.orig_fd_in = dup(STDIN_FILENO);
	if (g_data.orig_fd_in == -1)
		printf("msh: err backup stdin fd..\n");
	g_data.orig_fd_out = dup(STDOUT_FILENO);
	if (g_data.orig_fd_out == -1)
		printf("msh: err backup stdout fd..\n");
	g_data.stdin_to_default = 1;
	g_data.stdout_to_default = 1;
	if (env[0])
		get_env(env);
	else
		create_env();
	g_data.heredoc = NULL;
	ft_chdir(g_data.cwd);
	init_shlvl();
	update_datas_from_env();
	g_data.initialized = 1;
}
