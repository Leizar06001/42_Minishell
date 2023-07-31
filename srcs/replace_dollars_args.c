/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:02:03 by mabdali           #+#    #+#             */
/*   Updated: 2023/07/31 14:46:32 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int c_l_len(char **cmd_line)
{
    int len;

    len = 0;
    if (cmd_line == NULL)
        return (len);
    while (cmd_line[len] != NULL)
        len++;
    return (len);
}

char    *get_env_variable(const char *var_name)
{
    int var_name_len;
    int i;

    i = 0;
    var_name_len = strlen(var_name);
    while (g_data.env[i] != NULL)
    {
        if (strncmp(g_data.env[i], var_name, var_name_len) == 0
            && g_data.env[i][var_name_len] == '=')
            return (strdup(g_data.env[i] + var_name_len + 1));
        i++;
    }
    return (NULL);
}

char    *replace_dollar_var(const char *arg)
{
    char    *var_name;
    char    *value;
    int     i;
    char    *tmp;

    i = 0;
    g_data.quote_before_dquotedollar = 0;
    if (arg[0] =='\'')
    {
        arg = arg + 1;
        while (arg[i] && arg[i] != '\'')
            i++;
        tmp = malloc(sizeof(char) * (i + 1));
        i = 0;
        while (arg[i] && arg[i] != '\'')
        {
            tmp[i] = arg[i];
            i++;
        }
        tmp[i] = '\0';
        return (tmp);
    }
    else if (arg[0] == '\"')
    {
        arg = arg + 1;
        while (arg[i] && arg[i] != '\"')
            i++;
        tmp = malloc(sizeof(char) * (i + 1));
        i = 0;
        while (arg[i] && arg[i] != '\"')
        {
            tmp[i] = arg[i];
            i++;
        }
        tmp[i] = '\0';
        arg = ft_strdup(tmp);
    }
    i = 0;
    while (arg[i] && arg[i] != '$')
        i++;
    i = 0;
    tmp = malloc(sizeof(char) * (i + 1));
    while (arg[i] && arg[i] != '$')
    {
        tmp[i] = arg[i];
        i++;
    }
    tmp[i] = '\0';
    if (arg[i] == '$' && arg[i + 1] == '?')
        return (ft_itoa(g_data.exit_status));
    else if (arg[i] == '$')
    {
        var_name = strdup(arg + i + 1);
        if (var_name[ft_strlen(var_name) - 1] == '\'')
        {
            g_data.quote_before_dquotedollar = 1;
            var_name[ft_strlen(var_name) - 1] = '\0';
        }
        value = get_env_variable(var_name);
        if (g_data.quote_before_dquotedollar == 1)
            value = ft_strjoin(value, "\'");
        free(var_name);
        if (value == NULL)
            return (tmp);
        value = ft_strjoin(tmp, value);
        return (value);
    }
    return (strdup(arg));
}

char    **replace_dollar_args(char **cmd_line)
{
    char    **new_c_l;
    int     i;

    i = 0;
    new_c_l = (char **)malloc(sizeof(char *) * (c_l_len(cmd_line) + 1));
    if (new_c_l == NULL)
        return (NULL);
    while (cmd_line[i] != NULL)
    {
        new_c_l[i] = replace_dollar_var(cmd_line[i]);
        i++;
    }
    new_c_l[i] = NULL;
    return (new_c_l);
}
