/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:03 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/20 13:16:25 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	data.env = ft_arraydup(env);
	data.nb_env_var = ft_size_array(data.env);
	data.user = getenv("USER");
	data.path = getenv("PATH");
	data.home = getenv("HOME");
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
	data.current_folder = data.home;
	ft_chdir(data.home);
	data.user = ft_strjoin(BLUE, data.user);
	update_shell_name();
}
