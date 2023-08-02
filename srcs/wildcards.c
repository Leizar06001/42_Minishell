/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:56:05 by raphaellous       #+#    #+#             */
/*   Updated: 2023/08/02 15:01:06 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_add_array_to_array(char **src, char **dest, int pos, int found)
{
	char	**ret;
	int		size;
	int		i;
	int		j;

	size = ft_size_array(src) + ft_size_array(dest);
	ret = malloc(sizeof(char **) * (size + 1));
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (++i + j + 1 < size)
	{
		if (i == pos)
		{
			while (src[++j])
				ret[i + j] = ft_strdup(src[j]);
			found = 1;
		}
		ret[i + j + 1 + found * -1] = ft_strdup(dest[i + found]);
	}
	ret[size - 1] = NULL;
	return (ret);
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

static void	ft_wildcards_add_to_cmd(int nb_cards)
{
	char	**ret;

	(void)nb_cards;
	ret = ft_add_array_to_array(g_data.wildcard_res, g_data.cur_cmd,
			g_data.actual_arg, 0);
	free_2d(g_data.cur_cmd);
	g_data.cur_cmd = ret;
	g_data.actual_arg += nb_cards;
}

char	*ft_wildcards_main(void)
{
	int		fd;
	int		ret;

	g_data.wildcard_res = malloc(sizeof(char *) * 1);
	g_data.wildcard_res[0] = NULL;
	g_data.cur_args = malloc(sizeof(char *) * 2);
	g_data.cur_args[0] = ft_strdup("ls");
	g_data.cur_args[1] = NULL;
	ft_do_redir(">", ".temp_wildcards");
	ft_cmd_laucher_main(NOPIPE);
	fd = open(".temp_wildcards", O_RDONLY);
	ret = ft_wildcards_read_file(fd, g_data.cur_cmd[g_data.actual_arg]);
	close(fd);
	ft_reset_redirs();
	unlink(".temp_wildcards");
	if (ret)
		ft_wildcards_add_to_cmd(ret);
	else
		g_data.actual_arg++;
	free_2d(g_data.cur_args);
	free_2d(g_data.wildcard_res);
	return (NULL);
}
