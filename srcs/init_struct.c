/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:03 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/31 17:40:25 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

void	init_shlvl(void)
{
	char	*shlvl_val;
	char	*new_val;
	int		shlvl_int;
	char	**a;

	a = malloc(sizeof(char *) * 4);
	if (!a)
		return ;
	shlvl_int = 1;
	shlvl_val = ft_getvar("SHLVL");
	if (shlvl_val)
		shlvl_int = ft_atoi(shlvl_val) + 1;
	new_val = ft_strjoin("SHLVL=", ft_itoa(shlvl_int));
	a[0] = ft_strdup("export");
	a[1] = new_val;
	a[2] = NULL;
	ft_export(a);
	free(a[0]);
	free(a[1]);
	free(a);
}

static void	get_env(char **env)
{
	g_data.env = ft_arraydup_plus_one(env);
	g_data.nb_env_var = ft_size_array(g_data.env);
	g_data.cwd = getenv("PWD");
}

static void	create_env(void)
{
	g_data.cwd = "/";
	g_data.env = (char **)malloc(sizeof(char *) * 2);
	g_data.env[0] = ft_strdup("PWD=/");
	g_data.env[1] = NULL;
	g_data.nb_env_var = 1;
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
	{
		if (g_data.path_lst[0])
			free_2d(g_data.path_lst);
		else
			free(g_data.path_lst);
	}
	if (g_data.path)
		g_data.path_lst = ft_split(g_data.path, ':');
	else
	{
		g_data.path_lst = (char **)malloc(sizeof(char *) * 1);
		g_data.path_lst[0] = NULL;
	}
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
	update_datas_from_env();
	ft_chdir(g_data.cwd);
	init_shlvl();
	g_data.initialized = 1;
}
