/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_fnc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:36:08 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/26 14:21:09 by mabdali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arg_list(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	**arg_list(char **cmd_line)
{
	int		i;
	int		j;
	char	**args;

	i = 0;
	j = 0;
	while (cmd_line[i])
		i++;
	args = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cmd_line[i])
	{
		args[j] = ft_strdup(cmd_line[i]);
		i++;
		j++;
	}
	args[j] = NULL;
	return (args);
}

int	find_fnc_path(char **cmd_line)
{
	int		i;
	char	*tmp;
	char	*fnc_slash;

	i = 0;
	fnc_slash = ft_strjoin("/", cmd_line[0]);
	while (data.path_lst[i])
	{
		tmp = ft_strjoin(data.path_lst[i], fnc_slash);
		if (access(tmp, F_OK) == 0)
		{
			data.path_fnc = ft_strdup(tmp);
			free(tmp);
			free(fnc_slash);
			return (0);
		}
		i++;
		free(tmp);
	}
	free(fnc_slash);
	return (1);
}

int	exec_fnc_from_path(char **cmd_line)
{
	char	path[255];

	if (cmd_line[0][0] == '.')
		data.path_fnc = ft_strjoin(getcwd(path, 255), cmd_line[0] + 1);
	else if (cmd_line[0][0] == '/')
		data.path_fnc = cmd_line[0];
	if (access(data.path_fnc, F_OK) == 0)
		return (0);
	return (1);
}

int	ft_execve(char **cmd_line)
{
	pid_t	pid;
	char	**args;
	int		err;

	args = arg_list(cmd_line);
	if (args[0][0] == '.' || args[0][0] == '/')
		err = exec_fnc_from_path(args);
	else
		err = find_fnc_path(cmd_line);
	if (err)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (execve(data.path_fnc, args, data.env) == -1)
			printf("error exec\n");
		exit(1);
	}
	else
		waitpid(0, NULL, 0);
	free_arg_list(args);
	return (0);
}
