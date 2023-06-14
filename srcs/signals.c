/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:51:27 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/14 14:42:49 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
    if (sig == SIGINT)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        printf("\n%s", data.minishell_name);
    }
    else if (sig == SIGQUIT)
    {

    }
}

