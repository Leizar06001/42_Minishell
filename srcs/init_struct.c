/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:03 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/27 13:18:23 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

void	update_shell_name(void)
{
	char	path[255];
	char	*tmp;
	char	*tmp2;

	getcwd(path, 255);
	tmp = ft_strjoin(g_data.user, "@minishell:"YELLOW);
	if (g_data.home)
	{
		if (strcmp(g_data.home, path) == 0)
			tmp2 = ft_strjoin(tmp, "~");
		else
			tmp2 = ft_strjoin(tmp, g_data.current_folder);
	}
	else
		tmp2 = ft_strjoin(tmp, g_data.current_folder);
	if (g_data.minishell_name)
		free(g_data.minishell_name);
	g_data.minishell_name = ft_strjoin(tmp2, NC"$ ");
	free(tmp);
	free(tmp2);
}

void	get_env(char **env)
{
	g_data.env = ft_arraydup_plus_one(env);
	g_data.nb_env_var = ft_size_array(g_data.env);
	g_data.user = getenv("USER");
	g_data.path = getenv("PATH");
	g_data.home = getenv("HOME");
	g_data.cwd = getenv("PWD");
	g_data.path_lst = ft_split(g_data.path, ':');
}

void	create_env(void)
{
	g_data.env = (char **)malloc(sizeof(char *) * 1);
	g_data.env[0] = NULL;
	g_data.nb_env_var = 0;
	g_data.user = "no-env";
	g_data.path = NULL;
	g_data.home = NULL;
	g_data.cwd = "/";
	g_data.path_lst = (char **)malloc(sizeof(char *) * 1);
	g_data.path_lst[0] = NULL;
}

void	init_struct(char **env)
{
	g_data.exit = 0;
	g_data.env = NULL;
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
	g_data.user = ft_strjoin(BLUE, g_data.user);
	ft_chdir(g_data.cwd);
	g_data.heredoc = NULL;
}
