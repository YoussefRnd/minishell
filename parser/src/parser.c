/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:27:02 by yboumlak          #+#    #+#             */
/*   Updated: 2024/08/06 17:11:11 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_token	*copy_token(t_token *original)
{
	t_token	*copy;

	copy = malloc(sizeof(t_token));
	if (copy == NULL)
		return (NULL);
	copy->type = original->type;
	copy->value = ft_strdup(original->value);
	if (copy->value == NULL)
	{
		free(copy);
		return (NULL);
	}
	copy->next = NULL;
	copy->subtokens = NULL;
	copy->state = original->state;
	copy->is_atached = original->is_atached;
	return (copy);
}

bool	match_pattern(char *pattern, char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (true);
	if (*pattern == '*' && *str == '.')
		return (false);
	if (*pattern == '*' && *(pattern + 1) != '\0' && *str == '\0')
		return (false);
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	if (*pattern == '*')
		return (match_pattern(pattern + 1, str) || match_pattern(pattern, str
				+ 1));
	return (false);
}

void	sort_array(char **array)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**expand_wildcard(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	char			**new_matches;
	int				size;
	int				i;

	size = 10;
	matches = malloc(sizeof(char *) * size);
	if (matches == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		free(matches);
		return (NULL);
	}
	entry = readdir(dir);
	i = 0;
	while (entry != NULL)
	{
		if (match_pattern(pattern, entry->d_name))
		{
			if (i >= size)
			{
				size *= 2;
				new_matches = ft_realloc(matches, sizeof(char *) * size);
				if (new_matches == NULL)
				{
					perror("malloc");
					free_array(matches);
					closedir(dir);
					return (NULL);
				}
				matches = new_matches;
			}
			matches[i] = ft_strdup(entry->d_name);
			if (matches[i] == NULL)
			{
				perror("malloc");
				free_array(matches);
				closedir(dir);
				return (NULL);
			}
			i++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (i == 0)
	{
		free(matches);
		matches = NULL;
	}
	else
	{
		new_matches = ft_realloc(matches, sizeof(char *) * (i + 1));
		if (new_matches == NULL)
		{
			perror("malloc");
			free_array(matches);
			return (NULL);
		}
		matches = new_matches;
		matches[i] = NULL;
		sort_array(matches);
	}
	return (matches);
}

t_tree_node	*create_tree_node(t_token *token)
{
	t_tree_node	*node;

	node = malloc(sizeof(t_tree_node));
	if (token != NULL)
		node->token = copy_token(token);
	else
		node->token = NULL;
	node->left = NULL;
	node->right = NULL;
	node->redirections = NULL;
	return (node);
}

t_tree_node	*parse_subshell(t_token **tokens)
{
	t_tree_node	*node;
	t_token		*subshell_tokens;
	t_token		*token;

	if (*tokens == NULL || (*tokens)->type != TOKEN_SUBSHELL)
		return (NULL);
	token = *tokens;
	subshell_tokens = token->subtokens;
	node = create_tree_node(token);
	*tokens = (*tokens)->next;
	node->left = parse(&subshell_tokens);
	return (node);
}

t_tree_node	*parse_command(t_token **tokens)
{
	t_tree_node		*node;
	t_tree_node		*current;
	t_tree_node		*subshell_node;
	t_redirection	*redirections;
	char			*value;
	t_token			*next;
	t_redirection	*new_redir;
	t_redirection	*last_redir;
	char			**matches;
	t_token			*new_token;
	int				i;

	node = NULL;
	current = NULL;
	subshell_node = NULL;
	redirections = NULL;
	while (*tokens && ((*tokens)->type != TOKEN_EOF
			&& (*tokens)->type != TOKEN_PIPE && (*tokens)->type != TOKEN_AND
			&& (*tokens)->type != TOKEN_OR))
	{
		if ((*tokens)->type == TOKEN_WHITESPACE
			|| (*tokens)->type == TOKEN_EMPTY)
		{
			*tokens = (*tokens)->next;
			continue ;
		}
		if ((*tokens)->type == TOKEN_SUBSHELL)
		{
			subshell_node = parse_subshell(tokens);
			if (node == NULL)
			{
				node = subshell_node;
				current = node;
			}
			else
			{
				current->right = subshell_node;
				current = current->right;
			}
			continue ;
		}
		if ((*tokens)->type == TOKEN_REDIR_IN
			|| (*tokens)->type == TOKEN_REDIR_OUT
			|| (*tokens)->type == TOKEN_REDIR_APPEND
			|| (*tokens)->type == TOKEN_HEREDOC)
		{
			new_redir = parse_redirection(tokens);
			if (new_redir == NULL)
			{
				free_tree(&node);
				return (NULL);
			}
			if (redirections == NULL)
				redirections = new_redir;
			else
			{
				last_redir = redirections;
				while (last_redir->next)
					last_redir = last_redir->next;
				last_redir->next = new_redir;
			}
			continue ;
		}
		if ((*tokens)->type == TOKEN_WORD || (*tokens)->type == TOKEN_ERROR
			|| (*tokens)->type == TOKEN_BUILTIN
			|| (*tokens)->type == TOKEN_WILDCARD)
		{
			while ((*tokens)->next && ((*tokens)->next->type == TOKEN_WORD
					|| (*tokens)->next->type == TOKEN_WILDCARD))
			{
				value = ft_strjoin((*tokens)->value, (*tokens)->next->value);
				free((*tokens)->value);
				(*tokens)->value = value;
				if ((*tokens)->next->type == TOKEN_WILDCARD)
					(*tokens)->type = TOKEN_WILDCARD;
				next = (*tokens)->next;
				(*tokens)->next = next->next;
				free(next);
			}
		}
		if ((*tokens)->type == TOKEN_WILDCARD)
		{
			matches = expand_wildcard((*tokens)->value);
			if (matches)
			{
				i = 0;
				while (matches[i])
				{
					new_token = create_token(TOKEN_WORD, ft_strdup(matches[i]),
							NORMAL);
					if (new_token == NULL)
					{
						free_array(matches);
						free_tree(&node);
						return (NULL);
					}
					if (node == NULL)
					{
						node = create_tree_node(new_token);
						free_token(&new_token);
						if (node == NULL)
						{
							free_token(&new_token);
							free_array(matches);
							return (NULL);
						}
						current = node;
					}
					else
					{
						current->right = create_tree_node(new_token);
						free_token(&new_token);
						if (current->right == NULL)
						{
							free_token(&new_token);
							free_array(matches);
							free_tree(&node);
							return (NULL);
						}
						current = current->right;
					}
					i++;
				}
				free_array(matches);
				*tokens = (*tokens)->next;
				continue ;
			}
		}
		if (((*tokens)->type == TOKEN_ENV
				|| (*tokens)->type == TOKEN_SPECIAL_VAR) && (*tokens)->next
			&& (*tokens)->next->type == TOKEN_WORD)
		{
			(*tokens)->is_atached = true;
		}
		if (node == NULL)
		{
			node = create_tree_node(*tokens);
			current = node;
			if (redirections)
			{
				attach_redirections(node, redirections);
				redirections = NULL;
			}
		}
		else
		{
			current->right = create_tree_node(*tokens);
			current = current->right;
		}
		*tokens = (*tokens)->next;
	}
	if (node && redirections)
		attach_redirections(node, redirections);
	return (node);
}

t_tree_node	*parse_pipe(t_token **tokens)
{
	t_tree_node	*left;
	t_tree_node	*node;

	left = parse_command(tokens);
	while (*tokens != NULL && (*tokens)->type == TOKEN_PIPE)
	{
		node = create_tree_node(*tokens);
		*tokens = (*tokens)->next;
		node->left = left;
		node->right = parse_command(tokens);
		left = node;
	}
	return (left);
}

t_tree_node	*parse_and_or(t_token **tokens)
{
	t_tree_node	*left;
	t_tree_node	*node;

	left = parse_pipe(tokens);
	while (*tokens != NULL && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		node = create_tree_node(*tokens);
		*tokens = (*tokens)->next;
		node->left = left;
		node->right = parse_pipe(tokens);
		left = node;
	}
	return (left);
}

t_tree_node	*parse(t_token **tokens)
{
	return (parse_and_or(tokens));
}

void	print_token(t_token *token)
{
	if (token == NULL)
		return ;
	printf("Token type: %d, value: %s, state: %d\n", token->type, token->value,
		token->state);
	if (token->subtokens != NULL)
	{
		printf("Subtokens:\n");
		print_token(token->subtokens);
	}
	if (token->next != NULL)
	{
		printf("Next token:\n");
		print_token(token->next);
	}
}

void	print_redirections(t_redirection *redirection, char *indent)
{
	while (redirection != NULL)
	{
		printf("%sRedirection type: %d, file: %s, delimiter: %s\n", indent,
			redirection->type, redirection->file,
			redirection->delimiter ? redirection->delimiter : "NULL");
		printf("%sFile descriptor: %d\n", indent, redirection->fd);
		redirection = redirection->next;
	}
}

void	print_tree(t_tree_node *node, char *indent, bool is_last)
{
	char	new_indent[100];

	if (node == NULL)
		return ;
	printf("%s", indent);
	strcpy(new_indent, indent);
	if (is_last)
	{
		printf("└──");
		strcat(new_indent, "    ");
	}
	else
	{
		printf("├──");
		strcat(new_indent, "│   ");
	}
	if (node->token)
		printf("%s, %u, %d\n", node->token->value, node->token->type,
			node->token->is_atached);
	else
		printf("NULL\n");
	print_redirections(node->redirections, new_indent);
	if (node->left || node->right)
	{
		if (node->left)
			print_tree(node->left, new_indent, node->right == NULL);
		if (node->right)
			print_tree(node->right, new_indent, true);
	}
}
