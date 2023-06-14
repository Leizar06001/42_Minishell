/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdali <mabdali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/14 11:07:16 by mabdali          ###   ########.fr       */
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
	char	***input;
	char	s[100];
	int i;

	i = 0;
	input = malloc(sizeof(char *) * (10 + 1));
if (input == NULL) {
    // Gérer l'échec de l'allocation mémoire
    return 0;
}
input[10] = NULL; // Assurez-vous de terminer le tableau avec NULL
	while (data.cmd[i])
	{
	input[i] = ft_split_spaces(data.cmd[i]);
	if (input[i][0] == NULL)
		return (0);
	if (!ft_strcmp(input[i][0], "cd") || !ft_strcmp(input[i][0], "chdir"))
		ft_chdir(input[i][1]);
	else if (!ft_strcmp(input[i][0], "pwd"))
		printf("%s\n", getcwd(s, 100));
	else if (!ft_strcmp(input[i][0], "echo"))
		ft_echo(input[i]);
	else if (!ft_strcmp(input[i][0], "exit"))
		return (1);
	else
		printf("shell: command not found: %s\n", input[i][0]);
	i++;
	}
	return (0);
}

// int	exec_cmd(void)
// {
// 	char	**input;
// 	char	s[100];

// 	input = ft_split_spaces(data.line);
// 	if (input[0] == NULL)
// 		return (0);
// 	if (!ft_strcmp(input[0], "cd") || !ft_strcmp(input[0], "chdir"))
// 		ft_chdir(input[1]);
// 	else if (!ft_strcmp(input[0], "pwd"))
// 		printf("%s\n", getcwd(s, 100));
// 	else if (!ft_strcmp(input[0], "echo"))
// 		ft_echo(input);
// 	else if (!ft_strcmp(input[0], "exit"))
// 		return (1);
// 	else
// 		printf("shell: command not found: %s\n", input[0]);
// 	return (0);
// }

char	*ft_strdup(char *s)
{
	char *str;
	int i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	main(void)
{
	//extern char **environ;	// env var set (maybe used to export new vars without using setenv())
	
	printf("** Initialization **\n");
	init_struct();
	find_sys_functions();
	printf("** Init Done **\n\n");
	int i = 0;
	while (1)
	{
		data.line = readline(data.minishell_name);
		if(ft_strrchr(data.line, ';'))
		{
			data.cmd = ft_split(data.line, ';');
			while (data.cmd[i])
			{
				add_history(data.cmd[i]);
				i++;
			}
		}
		else
		{
			data.cmd = malloc(sizeof(char *) * 2);
			data.cmd[0] = ft_strdup(data.line);
			data.cmd[1] = NULL;
		add_history(data.line);
		}
		if (exec_cmd() == 1)
			break ;
	}
	return (0);
	//free_struct();
}

// int	main(void)
// {
// 	//extern char **environ;	// env var set (maybe used to export new vars without using setenv())
	
// 	printf("** Initialization **\n");
// 	init_struct();
// 	find_sys_functions();
// 	printf("** Init Done **\n\n");
// 	int i = 0;
// 	while (1)
// 	{
// 		data.line = readline(data.minishell_name);
// 		if(ft_strrchr(data.line, ';'))
// 		{
// 			data.cmd = ft_split(data.line, ';');
// 			while (data.cmd[i])
// 			{
// 				add_history(data.cmd[i]);
// 				i++;
// 			}
// 		}
// 		else
// 		{
// 			data.cmd = malloc(sizeof(char *) * 2);
// 			data.cmd[0] = ft_strdup(data.line);
// 			data.cmd[1] = NULL;
// 		add_history(data.line);
// 		}
// 		if (exec_cmd() == 1)
// 			break ;
// 	}
// 	return (0);
// 	//free_struct();
// }