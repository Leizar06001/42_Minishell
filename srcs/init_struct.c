/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:03 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/20 12:16:59 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <string.h>
void	update_shell_name()
{
	char	path[255];
	char	*tmp;
	char	*tmp2;

	getcwd(path, 255);
	tmp = ft_strjoin(data.user, "@minishell:"YELLOW);
	if (strcmp(data.home, path) == 0)
		tmp2 = ft_strjoin(tmp, "~");
	else
		tmp2 = ft_strjoin(tmp, data.current_folder);
	if (data.minishell_name)
		free(data.minishell_name);
	data.minishell_name = ft_strjoin(tmp2, NC"$ ");
	free(tmp);
	free(tmp2);
}

void	get_env(char **env)
{
	data.env = ft_arraydup_plus_one(env);
	data.nb_env_var = ft_size_array(data.env);
	data.user = getenv("USER");
	data.path = getenv("PATH");
	data.home = getenv("HOME");
	data.cwd = getenv("PWD");
	data.path_lst = ft_split(data.path, ':');
}

void	create_env()
{
	data.env = (char **)malloc(sizeof(char *) * 1);
	data.env[0] = NULL;
	data.nb_env_var = 0;
	data.user = "no-env";
	data.path = "/";
	data.home = "/";
	data.cwd= "/";
	data.path_lst = (char **)malloc(sizeof(char *) * 1);
	data.path_lst[0] = NULL;
}

void	init_struct(char **env)
{
	data.exit = 0;
	data.env = NULL;
	data.minishell_name = NULL;
	data.output = NULL;
	if (env[0])
		get_env(env);
	else
		create_env();
	data.user = ft_strjoin(BLUE, data.user);
	ft_chdir(data.cwd);
}
