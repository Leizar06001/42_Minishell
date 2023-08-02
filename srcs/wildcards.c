/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:56:05 by raphaellous       #+#    #+#             */
/*   Updated: 2023/08/02 08:14:18 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_add_array_to_array(char **src, char **dest, int pos)
{
	char	**ret;
	int		size;
	int		i;
	int		j;
	int		found;

	size = ft_size_array(src) + ft_size_array(dest);
	ret = malloc(sizeof(char **) * (size + 1));
	found = 0;
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (++i + j + 1 < size)
	{
		if (i == pos)
		{
			while (src[++j])
				ret[i + j] = src[j];
			found = 1;
		}
		ret[i + j + 1 + found * -1] = dest[i + found];
	}
	ret[i + j + 1] = NULL;
	return (ret);
}

static void	ft_wildcards_add_to_cmd(int nb_cards)
{
	char	**ar1;
	char	**ret;

	(void)nb_cards;
	ar1 = malloc(sizeof(char *) * 10);
	ar1[0] = ft_strdup("0000");
	ar1[1] = ft_strdup("1111");
	ar1[2] = ft_strdup("2222");
	ar1[3] = ft_strdup("3333");
	ar1[4] = ft_strdup("4444");
	ar1[5] = NULL;
	ret = ft_add_array_to_array(g_data.wildcard_res, ar1, 2);
	prt_args(ret);
}

static int	match(const char *pattern, const char *word)
{
	while (*pattern && *word)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			while (*word)
			{
				if (match(pattern, word))
					return (1);
				word++;
			}
			return (*pattern == '\0');
		}
		if (*pattern != *word)
			return (0);
		pattern++;
		word++;
	}
	return (*pattern == *word);
}

static int	ft_wildcards_read_file(int fd, char *pattern)
{
	char	*line;
	int		nb_cards;
	char	**tmp;

	nb_cards = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		if (match(pattern, line))
		{
			tmp = ft_arraydup_plus_one(g_data.wildcard_res);
			free_2d(g_data.wildcard_res);
			tmp[nb_cards] = ft_strdup(line);
			tmp[nb_cards + 1] = NULL;
			g_data.wildcard_res = tmp;
			nb_cards++;
		}
		if (line)
			free(line);
	}
	return (nb_cards);
}

int	ft_wildcards_main(char *cmd)
{
	int		err;
	int		fd;
	int		ret;

	(void)cmd;
	g_data.wildcard_res = malloc(sizeof(char *) * 1);
	g_data.wildcard_res[0] = NULL;
	g_data.cur_args = malloc(sizeof(char *) * 2);
	g_data.cur_args[0] = ft_strdup("ls");
	g_data.cur_args[1] = NULL;
	err = ft_do_redir(">", ".temp_wildcards");
	err = ft_cmd_laucher_main(NOPIPE);
	fd = open(".temp_wildcards", O_RDONLY);
	ret = ft_wildcards_read_file(fd, cmd);
	close(fd);
	ft_reset_redirs();
	unlink(".temp_wildcards");
	ft_wildcards_add_to_cmd(ret);
	free_2d(g_data.cur_args);
	free_2d(g_data.wildcard_res);
	return (err);
}
