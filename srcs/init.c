/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:50:42 by rloussig          #+#    #+#             */
/*   Updated: 2023/08/01 13:23:19 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*shell_name_err(void)
{
	char	*tmp;
	char	*tmp2;
	char	*err_nb;

	err_nb = ft_itoa(g_data.exit_status);
	tmp = ft_strjoin(RED"X ", err_nb);
	tmp2 = ft_strjoin(tmp, " ");
	free(tmp);
	tmp = ft_strjoin(tmp2, g_data.user);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, "@minishell:"YELLOW);
	free(tmp);
	free(err_nb);
	return (tmp2);
}

void	update_shell_name(void)
{
	char	path[255];
	char	*tmp;
	char	*tmp2;

	getcwd(path, 255);
	if (!g_data.exit_status)
		tmp = ft_strjoin(g_data.user, "@minishell:"YELLOW);
	else
		tmp = shell_name_err();
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
