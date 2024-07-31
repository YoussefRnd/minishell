/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:14:12 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/31 18:34:25 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"
#include "../../parser/inc/parser.h"

int respond_to_b(t_tree_node *cmd, t_env **env)
{
    if (ft_strcmp(cmd->token->value, "cd") == 0)
        return respond_to_cd(cmd->right, env);
    // else if (ft_strcmp(cmd->token->value, "env") == 0)
    //     return respond_to_env(*env);
    // else if (ft_strcmp(cmd->token->value, "export") == 0)
    //     return respond_to_export(cmd, env);
    // else if (ft_strcmp(cmd->token->value, "unset") == 0)
    //     return respond_to_unset(cmd, env);
    // else if (ft_strcmp(cmd->token->value, "exit") == 0)
    //     return respond_to_exit(cmd, env);
    // else if (ft_strcmp(cmd->token->value, "pwd") == 0)
    //     return respond_to_pwd(cmd, env);
    // else if (ft_strcmp(cmd->token->value, "echo") == 0)
    //     return respond_to_echo(cmd, env);
    // else
    return (0);
}


// int main(int ac, char **av, char **envp)
// {
//     t_tree_node *tree;

//     tree = malloc(sizeof(t_tree_node *));
//     tree->token = malloc(sizeof(t_token *));
//     tree->token->value = "env";
//     t_env *env = create_env_dict(envp);
//     respond_to_b(tree, &env);
// }