/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 09:50:59 by rloussig          #+#    #+#             */
/*   Updated: 2023/08/01 16:20:39 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_remain(char *buf)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (0);
	}
	str = ft_calloc((ft_strlen(buf) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buf[i + j])
	{
		str[j] = buf[i + j];
		j++;
	}
	str[j] = 0;
	free(buf);
	return (str);
}

char	*ft_return_line(char *buf)
{
	char	*str;
	int		i;

	i = 0;
	if (!buf[i])
		return (0);
	while (buf[i] && buf[i] != '\n')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		str[i] = buf[i];
		i++;
	}
	if (buf[i] && buf[i] == '\n')
		str[i] = '\n';
	return (str);
}

char	*ft_read_buf(int fd, char *ret)
{
	char	*buf;
	char	*tmp;
	int		byte_read;

	if (!ret)
		ret = ft_calloc(1, 1);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buf);
			return (0);
		}
		buf[byte_read] = 0;
		tmp = ft_strjoin(ret, buf);
		free(ret);
		ret = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*buf[256];
	char		*res;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (0);
	buf[fd] = ft_read_buf(fd, buf[fd]);
	if (!buf[fd])
		return (0);
	res = ft_return_line(buf[fd]);
	buf[fd] = ft_remain(buf[fd]);
	return (res);
}
