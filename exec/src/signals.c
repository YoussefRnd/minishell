/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:04:30 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/15 22:12:26 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

void	sigint_handler_in_p(int sig_num)
{
	(void)sig_num;
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
	g_status = 1;
}

void	signal_handler_in_p(void)
{
	signal(SIGINT, sigint_handler_in_p);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler_in_c(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
