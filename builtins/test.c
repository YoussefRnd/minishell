/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:26:52 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/20 13:30:44 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    char *str = strdup(av[1]);
    chdir(str);
    printf("je;o");
}