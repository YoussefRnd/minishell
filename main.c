/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:28:24 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/22 14:39:13 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
#include "lexer/inc/lexer.h"
#include "parser/inc/parser.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		char *input;
		t_token *tokens;
		t_tree_node *tree;
		input = readline("minishell$ ");
		tokens = tokenize(input);
		tree = parse(&tokens);
		print_tree(tree, "", true);
		// free_tokens(tokens);
		// free_tree(tree);
	}
	return (0);
}