/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdali <mabdali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/13 17:40:40 by mabdali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data data;

void	exex_echo(const char *arg)
{
    char *args[] = {"echo", (char *)arg, "qwe", "nbvcx", NULL};
	
    execve(data.path_fnc[0], args, NULL);
}

char* check_first_arg(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		while (str[i] != ' ')
			i++;
		tmp = malloc(i + 1);
		i = 0;
		while (str[i] != ' ')
        {
            tmp[i] = str[i];
            i++;
        }

		tmp[i] = '\0';
	}
	return (tmp);
}

char* check_second_arg(char *str)
{
    int		i;
	int		j;
	char	*tmp;
	int		size;
    i = 0;
	j = 0;
	size = ft_strlen(str);
	tmp = NULL;
    while (str[i])
    {
        while (str[i] != ' ')
            i++;
		while (str[i] == ' ')
            i++;
		tmp = malloc(size - i + 1);
		while (str[i])
        {
            tmp[j] = str[i];
            j++;
            i++;
        }
        tmp[j] = '\0';
    }
    return (tmp);
}

int	main(void)
{
	printf("** Initialization **\n");
	init_struct();
	find_sys_functions();
	printf("** Init Done **\n\n");

	//printf("\nPATH = %s\n", data.path);
	//printf("USER = %s\n", data.user);
	//printf("MINISHELL_NAME = %s\n\n", data.minishell_name);

	char ** input;
	
	// ************* TEST CD ****************
	char s[100];
	
    //printf("\n\n%s\n", getcwd(s, 100));
    //ft_chdir("/nfs/hmes");
    //printf("%s\n", getcwd(s, 100));
	
	while (1)
	{
		data.line = readline(data.minishell_name);

		input = ft_split_spaces(data.line);

		// int i = 0;
		// while(input[i])
		// {
		// 	printf("input[%d] > %s\n", i, input[i]);
		// 	i++;
		// }

		if (ft_strcmp(input[0], "cd") == 0 || ft_strcmp(input[0], "chdir") == 0)
			ft_chdir(input[1]);
		if (ft_strcmp(input[0], "pwd") == 0)
			printf("%s\n", getcwd(s, 100));
		if (ft_strcmp(input[0], "echo") == 0)
		{
			int i = 1;
			while(input[i])
			{
				printf("%s ", input[i]);
				i++;
			}
			printf("\n");
		}
			
		//exex_echo(check_second_arg(data.line));
		//printf("%s", data.line);
	}
	free_struct();
}
