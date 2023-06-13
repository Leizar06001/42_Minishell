/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:38:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/06/13 14:27:01 by mabdali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//t_data *data;
int main();

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*p1;
	char	*p2;

	i = 0;
	p1 = (char *)dest;
	p2 = (char *)src;
	if (p1 == NULL && p2 == NULL)
		return (NULL);
	while (i < n)
	{
		p1[i] = p2[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;

	if (!s1 || !s2)
		return (NULL);
	buffer = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!buffer)
		return (NULL);
	ft_memcpy(buffer, s1, ft_strlen(s1));
	ft_memcpy(buffer + ft_strlen(s1), s2, ft_strlen(s2));
	buffer[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (buffer);
}

void	init_struct(t_data *data)
{
	int	i;

	i = 0;
	data->user = getenv("USER");
	data->path = getenv("PATH");
	data->user = ft_strjoin(BLUE, data->user);
	data->user = ft_strjoin(data->user, NC);
	data->minishell_name = ft_strjoin(data->user, YELLOW"@minishell : "NC);
	data->path_fnc = (char **)malloc(sizeof(char *) * 10);
	while (i < 10)
	{
		data->path_fnc[i] = NULL;
		i++;
	}
}

int	find_fnc_path(char *fnc_name, char **path_lst, int index, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path_lst[i])
	{
		tmp = ft_strjoin(path_lst[i], fnc_name);
		if (access(tmp, F_OK) == 0)
		{
			printf("%s : %s\n", fnc_name, tmp);
			data->path_fnc[index] = (char *)malloc(sizeof(char) * ft_strlen(tmp) + 1);
			strcpy(data->path_fnc[index], tmp);
			free(tmp);
			break ;
		}
		i++;
		free(tmp);
	}
	return (0);
}

void	find_sys_functions(t_data *data)
{
	char	*path;
	char	**path_lst;

	path = getenv("PATH");
	path_lst = ft_split(path, ':');
	find_fnc_path("/chdir", path_lst, 0, data);
	find_fnc_path("/echo", path_lst, 1, data);
	find_fnc_path("/pwd", path_lst, 2, data);
	find_fnc_path("/export", path_lst, 3, data);
	find_fnc_path("/unset", path_lst, 4, data);
	find_fnc_path("/env", path_lst, 5, data);
	find_fnc_path("/exit", path_lst, 6, data);
	free(path_lst);
}

void	exex_echo(const char *arg, t_data *data)
{
    char *args[] = {"echo", (char *)arg, NULL};

    execve(data->path_fnc[1], args, NULL);
	main();
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
	t_data	data;

	init_struct(&data);
	find_sys_functions(&data);
	
	int i = 0;
    while(i < 10)
    {
        printf("%s \n", data.path_fnc[i]);
        i++;
    }

	printf("PATH = %s\n", data.path);
	printf("USER = %s\n", data.user);
	printf("MINISHELL_NAME = %s\n\n", data.minishell_name);
	while(1)
	{
	data.line = readline(data.minishell_name);
	//if (strcmp(check_first_arg(data.line), "echo"))
		exex_echo(check_second_arg(data.line), &data);
	printf("%s", data.line);
	}
	char *args[] = {"echo", "Hello, World!", NULL};
	execve(data.path_fnc[1], args, NULL);

}
