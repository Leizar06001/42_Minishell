/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:50:42 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/14 14:31:47 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    init_signals(void)
{
    data.sa.sa_sigaction = handler;
    sigemptyset(&data.sa.sa_mask);
    data.sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &data.sa, NULL);
}
