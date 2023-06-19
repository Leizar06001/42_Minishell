/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_fnc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:36:08 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/19 11:57:11 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_arg_list(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

char    **arg_list(char **cmd_line)
{
    int     i;
    int     j;
    char    **args;

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

int	find_fnc_path(char *fnc_name)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data.path_lst[i])
	{
		tmp = ft_strjoin(data.path_lst[i], fnc_name);
		if (access(tmp, F_OK) == 0)
		{
			data.path_fnc = ft_strdup(tmp);
			free(tmp);
			return (0);
		}
		i++;
		free(tmp);
	}
	return (1);
}

int	ft_execve(char **cmd_line)
{
	pid_t	pid;
	char	*fnc_slash;
    char    **args;
    int     err;

    args = arg_list(cmd_line);
    fnc_slash = ft_strjoin("/", cmd_line[0]);
    err = find_fnc_path(fnc_slash);
	if (err)
        return (1);
    pid = fork();
	if (pid == 0)
	{
		if (execve(data.path_fnc, args, NULL) == -1)
			printf("error\n");
		exit(1);
	}
	else
		waitpid(0, NULL, 0);
    free_arg_list(args);
    free(fnc_slash);
    return (0);
}
