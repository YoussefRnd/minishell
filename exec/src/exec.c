/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:26:23 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/23 10:11:50 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/temp.h"

void _execute(t_tree_node *tree)
{
    if(tree->token->type == TOKEN_WORD){
        cmd_execute(tree->token);
        return ;
    }
    else if (tree->token->type == TOKEN_PIPE){
        similar_popen(tree);
    }
}

void cmd_execute(t_tree_node *cmd)
{
    printf("cmd: %s\n", cmd->value);
    printf("args: %s\n", cmd->right->value);
}