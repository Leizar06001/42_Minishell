/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:07:50 by rloussig          #+#    #+#             */
/*   Updated: 2023/07/28 15:43:35 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	current_folder(void)
{
	char	*pos;
	char	*path;

	path = ft_getvar("PWD");
	pos = ft_strrchr(path, '/');
	g_data.current_folder = pos;
	update_shell_name();
}

static void	ft_export_pwd(char *new, char *old)
{
	char	**args;

	args = malloc(sizeof(char *) * 5);
	args[0] = ft_strdup("export");
	args[1] = ft_strjoin("PWD=", new);
	args[2] = ft_strjoin("OLDPWD=", old);
	args[3] = NULL;
	ft_export(args);
	free(args[2]);
	free(args[1]);
	free(args[0]);
	free(args);
}

void	ft_update_pwd(void)
{
	char	*old_pwd;
	char	new[1024];

	old_pwd = ft_getvar("PWD");
	getcwd(new, 1024);
	ft_export_pwd(new, old_pwd);
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
	{
		ft_update_pwd();
		current_folder();
	}
	return (ret);
}
