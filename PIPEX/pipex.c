#include "pipex.h"

t_data data;

int	find_fnc_path(char *fnc)
{
	int		i;
	char	*tmp;
    char	*fnc_slash;
    char    **list_path;

	i = 0;
    list_path = ft_split(getenv("PATH"), ':');
    fnc_slash = ft_strjoin("/", fnc);
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

int	ft_execve(char **cmd_line)
{
	pid_t	pid;
    char    *args[4] = {"ls", "-l", "-a", NULL};
    int     err;
	int		fd[2];
	int 	status;
	size_t	nbytes;
	char	buf[100];

	status = pipe(fd);
	if (status == -1)
	{
		printf("error pipe\n");
		exit(1);
	}
    pid = fork();
	if (pid == -1)
	{
		printf("error fork\n");
		exit(1);
	}
	if (pid == 0)
	{
		close(fd[1]);
		for (int i = 0; i < 2; i++){
			nbytes = read(fd[0], buf, 100);
			buf[nbytes] = 0;
			printf("%ld bytes > %s", nbytes, buf);
		}
		close(fd[0]);
		
		//if (execve(data.path_fnc, args, NULL) == -1)
		//	printf("error exec\n");
		exit(1);
	}
	else
	{
		usleep(1000000);
		printf("> WRITE HELLO\n");

		close(fd[0]);

		write(fd[1], "Hello\n", 6);

		usleep(1000000);
		printf("> WRITE WORLD\n");

		write(fd[1], " world\n", 7);

		usleep(1000000);
		printf("Close 1\n");

		close(fd[1]);
		waitpid(0, NULL, 0);
	}
	return (0);
}

void    main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	char buf[100];

	data.path_lst = ft_split(getenv("PATH"), ':');
	find_fnc_path("ls");
	printf("path_fnc: %s\n", data.path_fnc);
	ft_execve(argv);


}
