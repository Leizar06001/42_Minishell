/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:08:03 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/14 14:31:47 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_shell_name()
{
	char	path[255];

	getcwd(path, 255);
	data.minishell_name = ft_strjoin(data.user, "@minishell:"YELLOW);
	if (strcmp(data.home, path) == 0)
		data.minishell_name = ft_strjoin(data.minishell_name, "~");
	else
		data.minishell_name = ft_strjoin(data.minishell_name, data.current_folder);
	data.minishell_name = ft_strjoin(data.minishell_name, NC"$ ");
}

void	init_struct(char **env)
{
	init_signals();
	data.exit = 0;
	data.env = env;
	data.user = getenv("USER");
	data.path = getenv("PATH");
	data.home = getenv("HOME");
	data.current_folder = data.home;
	ft_chdir(data.home);
	data.user = ft_strjoin(BLUE, data.user);
	update_shell_name();
}

int	find_fnc_path(char *fnc_name, char **path_lst, int index)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path_lst[i])
	{
		tmp = ft_strjoin(path_lst[i], fnc_name);
		if (access(tmp, F_OK) == 0)
		{
			printf("%d > %s : %s\n", index, fnc_name, tmp);
			data.path_fnc = (char *)malloc(sizeof(char) * ft_strlen(tmp) + 1);
			strcpy(data.path_fnc, tmp);
			free(tmp);
			break ;
		}
		i++;
		free(tmp);
	}
	return (0);
}

void	find_sys_functions()
{
	char	*path;
	char	**path_lst;

	path = getenv("PATH");
	path_lst = ft_split(path, ':');
	find_fnc_path("/echo", path_lst, 0);
	find_fnc_path("/pwd", path_lst, 1);
	find_fnc_path("/export", path_lst, 2);
	find_fnc_path("/unset", path_lst, 3);
	find_fnc_path("/env", path_lst, 4);
	find_fnc_path("/exit", path_lst, 5);
	free(path_lst);
}
