#include "pipex.h"

t_data data;

int	find_fnc_path(char *fnc, int ind)
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
			data.path_fnc[ind] = ft_strdup(tmp);
			printf("%s > %s\n", fnc, data.path_fnc[ind]);
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

void	ft_redir_input(int fd_redir, char *comment)
{
	data.orig_fd_in = dup(STDIN_FILENO);
	dup2(fd_redir, STDIN_FILENO);
}

void	ft_redir_output(int fd_redir, char *comment)
{
	data.orig_fd_out = dup(STDOUT_FILENO);
	dup2(fd_redir, STDOUT_FILENO);
}

void	init_pathfnc(int nb)
{
	int		i;

	data.path_fnc = malloc(sizeof(char *) * nb);
	if (!data.path_fnc)
		return ;
	i = 0;
	while (i < nb)
	{
		data.path_fnc[i] = NULL;
		i++;
	}
}

void	free_pathfnc(int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		free(data.path_fnc[i]);
		i++;
	}
	free(data.path_fnc);
}

int	ft_open_pipe(int *fd)
{
	int	status;

	status = pipe(fd);
	if (status == -1)
	{
		printf("PIPE ERROR\n");
		exit(1);
	}
	return (0);
}

int	ft_create_fork()
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
	{
		printf("error fork\n");
		exit(1);
	}
	return (pid);
}

void	ft_redir_pipe_read_to_stdin(int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	ft_redir_pipe_write_to_stdout(int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

int	ft_call_execve(char **cmd, int ind, int create_pipe)
{
	pid_t	pid;
	int		fd[2];
	char	buf[100];

	if (create_pipe)
		ft_open_pipe(fd);	// fd[1] write end / fd[0] read end
    pid = ft_create_fork();
	if (pid == 0)
	{
		if (create_pipe)	// redir output to pipe
			ft_redir_pipe_write_to_stdout(fd);
		if (execve(data.path_fnc[ind], cmd, NULL) == -1)
			printf("error exec\n");
		exit(1);
	}
	else
	{
		if (create_pipe)
			ft_redir_pipe_read_to_stdin(fd);
		waitpid(0, NULL, 0);
	}
	return (0);
}

int    main()
{
	int		argc = 6;
	char	*argv[7] = {"pipex", "in.txt", "grep a", "grep s", "wc -l", "out.txt", NULL};
	char	***cmd;
	int		files_fd[2];
	int		i;

	init_pathfnc(argc);
	data.path_lst = ft_split(getenv("PATH"), ':');

	cmd = malloc((argc - 2) * sizeof(char**));
	
	i = -1;
	while (++i < argc - 3)
	{
		cmd[i] = ft_split(argv[i + 2], ' ');
		find_fnc_path(cmd[i][0], i);
	}
	cmd[i] = NULL;
	
	files_fd[0] = open(argv[1], O_RDONLY);
	files_fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC | 0644);

	printf("\n");
	ft_redir_input(files_fd[0], "in.txt");
	i = -1;
	while (++i < argc - 4)
	{
		ft_call_execve(cmd[i], i, 1);
		if (i == 0)
			dup2(STDIN_FILENO, data.orig_fd_in);	// reset input
	}
	ft_redir_output(files_fd[1], "out.txt");
	ft_call_execve(cmd[i], i, 0);
	
	free_pathfnc(5);
	return (0);
}
