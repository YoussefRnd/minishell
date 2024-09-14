/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:28:24 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/14 16:34:55 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/inc/builtins.h"
#include "exec/inc/execution.h"
#include "inc/minishell.h"
#include "lexer/inc/lexer.h"
#include "parser/inc/parser.h"

void	free_forked_and_input(t_norm *this)
{
	free(this->forked);
	free(this->input);
}

int	free_resources(t_norm *this)
{
	free(this->forked);
	free(this->input);
	free_tokens(&this->head);
	free_tree(&this->tree);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_norm	this;

	(void)argc;
	(void)argv;
	this.envs = create_env_dict(envp);
	while (1)
	{
		signal_handler_in_p();
		this.forked = malloc(sizeof(bool));
		*(this.forked) = false;
		this.input = readline("minishell$ ");
		if (!this.input)
		{
			free_forked_and_input(&this);
			break ;
		}
		add_history(this.input);
		this.tokens = tokenize(this.input);
		this.head = this.tokens;
		this.tree = parse(&this.tokens);
		_execute(this.tree, &this.envs, this.forked);
		free_resources(&this);
	}
	free_env_list(&this.envs);
	return (0);
}
