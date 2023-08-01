/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:50:42 by rloussig          #+#    #+#             */
/*   Updated: 2023/08/01 11:05:59 by raphaellous      ###   ########.fr       */
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

void	init_shlvl(void)
{
	char	*shlvl_val;
	char	*new_val;
	char	*new_line;
	int		shlvl_int;
	char	**a;

	a = malloc(sizeof(char *) * 4);
	if (!a)
		return ;
	shlvl_int = 1;
	shlvl_val = ft_getvar("SHLVL");
	if (shlvl_val)
		shlvl_int = ft_atoi(shlvl_val) + 1;
	new_val = ft_itoa(shlvl_int);
	new_line = ft_strjoin("SHLVL=", new_val);
	free(new_val);
	a[0] = ft_strdup("export");
	a[1] = new_line;
	a[2] = NULL;
	ft_export(a);
	free(a[0]);
	free(a[1]);
	free(a);
}
