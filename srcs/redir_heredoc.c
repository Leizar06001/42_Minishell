/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:02:49 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/31 17:23:21 by raphaellous      ###   ########.fr       */
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

static int	heredoc_process_line(char **tmp, char **tmp2, char **heredoc)
{
	*tmp2 = replace_dollar_var(*tmp);
	free(*tmp);
	*tmp = ft_strjoin(*heredoc, *tmp2);
	free(*tmp2);
	free(*heredoc);
	*tmp2 = ft_strjoin(*tmp, "\n");
	free(*tmp);
	*heredoc = *tmp2;
	return (0);
}

int	input_heredoc(char *delimiter, int err)
{
	char	*heredoc;
	char	*tmp;
	char	*tmp2;

	heredoc = malloc(1);
	heredoc[0] = '\0';
	tmp2 = NULL;
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
		heredoc_process_line(&tmp, &tmp2, &heredoc);
	}
	err = heredoc_w_to_file(heredoc);
	return (err);
}
