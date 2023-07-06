/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:15:31 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/19 10:19:30 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    copy_env_rm_var(char **new_env, char *rm_var)
{
    int     i;
    int     j;
    char    **cur_var;
    int     removed;

    i = 0;
    j = 0;
    removed = 0;
    while (data.env[i])
    {
        cur_var = ft_split(data.env[i], '=');
        if (ft_strcmp(cur_var[0], rm_var) != 0)
        {
            new_env[j] = ft_strdup(data.env[i]);
            j++;
        }
        else
        {
            printf("[%d]%s removed\n", i, cur_var[0]);
            removed++;
        }  
        //free_2d(cur_var);
        i++;
    }
    data.nb_env_var -= removed;
}

void    prt_env(char **env)
{
    int i;

    printf(">>> prt_env\n");
    i = data.nb_env_var - 5;
    while (env[++i])
        printf("%s\n", env[i]);
    //printf("%s\n", env[i]);    
}

void    ft_unset(char **cmd)
{
    int     i;
    char    **new_env;

    i = 0;
    while (cmd[++i])
    {
        if (check_var_name(cmd[i]))
        {
            new_env = (char**)malloc(sizeof(char*) * (data.nb_env_var + 1));
            if (new_env == NULL)
                return ;
            copy_env_rm_var(new_env, cmd[i]);
            new_env[data.nb_env_var] = NULL;
            free_2d(data.env);
            data.env = new_env;
        }
        else
            printf("minishell: unset: '%s': not a valid identifier\n", cmd[i]);
    }
    printf("NB ENV VAR = %d\n", data.nb_env_var);
}
