/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/13 20:13:23 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data data;

void	exex_echo(const char *arg)
{
    char *args[] = {"echo", (char *)arg, "qwe", "nbvcx", NULL};
	
    execve(data.path_fnc[0], args, NULL);
}

int	exec_cmd(void)
{
	char	**input;
	char	s[100];
	
	input = ft_split_spaces(data.line);
	if (input[0] == NULL)
		return (0);
	if (!ft_strcmp(input[0], "cd") || !ft_strcmp(input[0], "chdir"))
		ft_chdir(input[1]);
	else if (!ft_strcmp(input[0], "pwd"))
		printf("%s\n", getcwd(s, 100));
	else if (!ft_strcmp(input[0], "echo"))
		ft_echo(input);
	else if (!ft_strcmp(input[0], "exit"))
		return (1);
	else
		printf("shell: command not found: %s\n", input[0]);
	return (0);
}

int	main(void)
{
	//extern char **environ;	// env var set (maybe used to export new vars without using setenv())
	
	printf("** Initialization **\n");
	init_struct();
	find_sys_functions();
	printf("** Init Done **\n\n");

	while (1)
	{
		data.line = readline(data.minishell_name);
		add_history(data.line);
		if (exec_cmd() == 1)
			break ;
	}
	return (0);
	//free_struct();
}
