/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:04:30 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/05 22:08:33 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

void	sigint_handler_in_p(int sig_num)
{
	// printf("ctr-c has been clicked\n");
	// exit(-1);
	// printf("in parent\n");
	(void)sig_num;
	// rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
}

// void sigint_handler_in_c(int sig_num){
//     printf("in here\n");
//     status = 130;
//     exit (-1);
// }

// void	sigquit_handler(int sig_num)
// {
// 	status = 131;
// 	exit(-1);
// }
void	signal_handler_in_p(void)
{
	signal(SIGINT, sigint_handler_in_p);
	signal(SIGQUIT, SIG_IGN);
}

// void	test(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	printf("\n");
// }
void	signal_handler_in_c(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// int main () {
//     signal(SIGINT, sigint_handler); /* Register signal handler */
//     while(1) {
//         printf("Running...\n");
//         sleep(1);
//     }
//     return (0);
// }