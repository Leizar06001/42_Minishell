/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:09:14 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/15 16:10:02 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_var_name(char *str)
{
    int i;

    i = -1;
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (0);
    while (str[++i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
    }
    return (1);
}

void    copy_env(char **new_env)
{
    int i;

    i = -1;
    while (++i < data.nb_env_var)
        new_env[i] = ft_strdup(data.env[i]);
    new_env[i] = NULL;
}

int    check_var_exists(char *var, char *new_line)
{
    int     i;
    char    **cur_var;

    i = -1;
    while (data.env[++i])
    {
        cur_var = ft_split(data.env[i], '=');
        if (ft_strcmp(cur_var[0], var) == 0)
        {
            free(data.env[i]);
            data.env[i] = ft_strdup(new_line);
            free_2d(cur_var);
            return (1);
        }
        free_2d(cur_var);
    }
    return (0);
}

void    ft_export(char **cmd)
{
    (void)cmd;
    char *cmdtest[100] = {"export", "A=12", "B='asdg sdfg'", "C=", "D+=f", "E", "PATH=0000", NULL};

    int     i;
    char    **new_var;
    char    **new_env;

    i = 0;
    while (cmdtest[++i])
    {
        if (ft_strchr(cmdtest[i], '='))
        {
            new_var = ft_split(cmdtest[i], '=');
            if (check_var_name(new_var[0]))
            {
                if (!check_var_exists(new_var[0], cmdtest[i]))
                {
                    new_env = (char**)malloc(sizeof(char*) * (data.nb_env_var + 2));
                    if (new_env == NULL)
                        return ;
                    copy_env(new_env);
                    new_env[data.nb_env_var] = ft_strdup(cmdtest[i]);
                    new_env[data.nb_env_var + 1] = NULL;
                    //free_2d(data.env);
                    //data.env = ft_arraydup(new_env);
                    data.env = new_env;
                    data.nb_env_var++;
                    //free_2d(new_env);
                }
            }
            else
                printf("minishell: export: '%s': not a valid identifier\n", new_var[0]);
            free_2d(new_var);
        }
    }
    printf("NB ENV VAR = %d\n", data.nb_env_var);
}
