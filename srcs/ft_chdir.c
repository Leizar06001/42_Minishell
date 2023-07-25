/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:07:50 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/25 18:50:08 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	current_folder(void)
{
	char	path[255];
	char	*pos;

	getcwd(path, 255);
	pos = ft_strrchr(path, '/');
	g_data.current_folder = pos;
	update_shell_name();
}

int	ft_chdir(char *str)
{
	int	ret;

	if (str == NULL)
	{
		if (g_data.home)
			ret = chdir(g_data.home);
		else
		{
			printf("msh: cd: HOME not set\n");
			return (127);
		}
	}
	else
		ret = chdir(str);
	if (ret == -1)
		printf("cd: no such file or directory: %s\n", str);
	else
		current_folder();
	return (ret);
}
