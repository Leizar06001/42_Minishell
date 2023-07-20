/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_launcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:33:42 by raphaellous       #+#    #+#             */
/*   Updated: 2023/07/20 16:58:57 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtin_fnc(char **cmd)
{
	char	s[255];
	
	if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "chdir"))
		ft_chdir(cmd[1]);
	else if (!ft_strcmp(cmd[0], "pwd"))
		printf("%s\n", getcwd(s, 255));
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env();
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd);
	else
		return (1);
	return (0);
}

int ft_cmd_laucher_main(int has_pipe)
{
    int err;
    (void)has_pipe;
    
    printf("\n--->>\n");
    err = 0;
    if (!ft_builtin_fnc(data.cur_args))
        printf("msh: Exec from builtin..\n");
    else if (!ft_strcmp(data.cur_args[0], "exit"))
		return (1);
    else
    {
        err = ft_execve();
        printf("msh: Exec from execve..\n");
    }
    ft_reset_redirs();
    printf("--->>\n\n");
    return (err);
}
