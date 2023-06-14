/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:51:27 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/14 15:19:06 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_int(int sig)
{
    (void)sig;
    
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    //printf("\n%s", data.minishell_name);
}

void    handler_quit(int sig)
{
    (void)sig;

    //rl_redisplay();
    //printf("\n%s", data.minishell_name);
}

// void    init_signals(void)
// {
//     data.sa.sa_sigaction = handler;
//     sigemptyset(&data.sa.sa_mask);
//     data.sa.sa_flags = SA_SIGINFO;
//     sigaction(SIGINT, &data.sa, NULL);
// }
