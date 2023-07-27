/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fnc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:15:42 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/27 18:58:43 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	heredoc_w_to_file(char *str)
{
	int		fd;
	int		err;
	char	*filename;
	int		i;

	err = 0;
	filename = ft_strjoin("./.heredoc_", ft_itoa((int)(long)str));
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("msh: error creating temp heredoc\n");
		return (-1);
	}
	g_data.heredoc = filename;
	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
	close(fd);
	err = input_file(filename);
	free(str);
	return (err);
}

int	input_heredoc(char *delimiter, int err)
{
	char	*heredoc;
	char	*tmp;
	char	*tmp2;

	heredoc = malloc(1);
	heredoc[0] = '\0';
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
			break ;
		if (ft_strcmp(tmp, delimiter) == 0)
		{
			free(tmp);
			break ;
		}
		tmp2 = ft_strjoin(heredoc, tmp);
		free(tmp);
		free(heredoc);
		tmp = ft_strjoin(tmp2, "\n");
		free(tmp2);
		heredoc = tmp;
	}
	err = heredoc_w_to_file(heredoc);
	return (err);
}

int	input_file(char *filename)
{
	int	err;

	err = 0;
	g_data.fd_redir_in = open(filename, O_RDONLY);
	if (g_data.fd_redir_in == -1)
	{
		printf("msh: no such file or directory: %s\n", filename);
		return (-1);
	}
	err = dup2(g_data.fd_redir_in, STDIN_FILENO);
	if (err == -1)
		printf("msh: error dup input fd\n");
	close(g_data.fd_redir_in);
	g_data.stdin_to_default = 0;
	return (err);
}

int	output_trunc(char *filename)
{
	int	err;

	err = 0;
	g_data.fd_redir_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (g_data.fd_redir_out == -1)
	{
		printf("msh: cannot create file: %s\n", filename);
		return (-1);
	}
	err = dup2(g_data.fd_redir_out, STDOUT_FILENO);
	if (err == -1)
		printf("msh: error dup output fd\n");
	close(g_data.fd_redir_out);
	g_data.stdout_to_default = 0;
	return (err);
}

int	output_append(char *filename)
{
	int	err;

	err = 0;
	g_data.fd_redir_out = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (g_data.fd_redir_out == -1)
	{
		printf("msh: cannot create file: %s\n", filename);
		return (-1);
	}
	err = dup2(g_data.fd_redir_out, STDOUT_FILENO);
	if (err == -1)
		printf("msh: error dup output fd\n");
	close(g_data.fd_redir_out);
	g_data.stdout_to_default = 0;
	return (err);
}

