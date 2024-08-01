/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:28:24 by yboumlak          #+#    #+#             */
/*   Updated: 2024/08/01 11:12:36 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
#include "lexer/inc/lexer.h"
#include "parser/inc/parser.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_token		*tokens;
	t_tree_node	*tree;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return (1);
		add_history(input);
		tokens = tokenize(input);
		if (!tokens)
		{
			free(input);
			continue ;
		}
		tree = parse(&tokens);
		print_tree(tree, "", true);
		// free_tree(&tree);
		// free_tokens(&tokens);
		free(input);
	}
	return (0);
}
