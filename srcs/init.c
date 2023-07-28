/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:50:42 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/28 09:50:12 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_shell_name(void)
{
	char	path[255];
	char	*tmp;
	char	*tmp2;

	getcwd(path, 255);
	tmp = ft_strjoin(g_data.user, "@minishell:"YELLOW);
	if (g_data.home)
	{
		if (strcmp(g_data.home, path) == 0)
			tmp2 = ft_strjoin(tmp, "~");
		else
			tmp2 = ft_strjoin(tmp, g_data.current_folder);
	}
	else
		tmp2 = ft_strjoin(tmp, g_data.current_folder);
	if (g_data.minishell_name)
		free(g_data.minishell_name);
	g_data.minishell_name = ft_strjoin(tmp2, NC"$ ");
	free(tmp);
	free(tmp2);
}
