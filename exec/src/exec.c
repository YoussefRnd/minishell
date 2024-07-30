/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:26:23 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/30 11:10:24 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/execution.h"
#include "../../builtins/inc/builtins.h"

int status;
void	_execute(t_tree_node *tree, t_env *env)
{
	pid_t	pid;
	int	pfd[2];
	if (!tree)
		return ;

	// status = malloc(sizeof(int));
	if (tree->token->type == TOKEN_WORD)
	{
		pid = fork();
		if (pid == 0)
			cmd_execute(tree, env);
		else
			wait(&status);
	}
	else if (tree->token->type == TOKEN_PIPE)
	{
		if (pipe(pfd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		
		if (!pid){
			close(pfd[0]);
			dup2(pfd[1], STDOUT_FILENO);
			_execute(tree->left, env);
			exit(EXIT_SUCCESS);
		}
		if (pid)
			pid = fork();                                                                                                                                            
		if (!pid){
			close(pfd[1]);
			dup2(pfd[0], STDIN_FILENO);
			_execute(tree->right, env);
			exit(EXIT_SUCCESS);
		}
		close(pfd[0]);
		close(pfd[1]);
		// to change
		wait(&status);
		wait(&status);
	}
	// i think the tokenezation got fucked up
	else if (tree->token->type == TOKEN_AND || tree->token->type == TOKEN_OR){
		// am a create a funct that work for them both and and or
		// so what i need to do is run the command and then check
		// if it worked succefully
		operators_deal(tree, env);
		//  printf("Status after wait: %d\n", status);
		// if (tree->token->type == TOKEN_AND)
		// 	printf("we got an and operator\n");
		// else if (tree->token->type == TOKEN_OR)
		// 	printf("we got an or operator\n");
	}
	else if (tree->token->type == TOKEN_SUBSHELL){
		pid = fork();
		if (!pid)
			_execute(tree->left, env);
		else
			wait(&status);
	}
	// TO WORK ON LATER 7ITASH HAD L9LAWI M3NKSH
	else if (tree->token->type == TOKEN_ENV)
	{
		char *value = get_value(env, tree->token->value);
		if (value){
		free(tree->token->value);
		tree->token->value = ft_strdup(value);
		// printf("%s\n", tree->token->value);
		// printf("inside of token env case\n");
		tree->token->type = TOKEN_WORD;
		_execute(tree, env);
		}
	}
	else if (tree->token->type == TOKEN_BUILTIN)
		respond_to_b(tree, &env);
}

void operators_deal(t_tree_node *tree, t_env *env)
{
	int exit_status;
	if (tree->left){
		_execute(tree->left, env);
		// return ;
		// exit(EXIT_SUCCESS);
	}
	else
		return ;
	// la lprocess sala normally , meaning mashi bsignal ola shi haja
	if (WIFEXITED(status)){
		exit_status = WEXITSTATUS(status);
		// printf("WIFEXITED: %d\n", WIFEXITED(status));
    	// printf("WEXITSTATUS: %d\n", WEXITSTATUS(status));
		if (tree->right){
				// printf("exit_status: %d\n", exit_status);
			if (exit_status == 0 && tree->token->type == TOKEN_AND){
				// printf("insid of and\n");
				_execute(tree->right, env);
			}
			else if (exit_status != 0 && tree->token->type == TOKEN_OR){
				// printf("token type: %u\n", tree->token->type);
				// printf("insid of or\n");
				_execute(tree->right, env);
			}
		}
	}
}

void	cmd_execute(t_tree_node *cmd, t_env *envps)
{
	char	**path_dirs;
	char	*path;
	char	**args;
	char	**env;

	// printf("cmd: %s\n", cmd->token->value);
	// printf("args: %s\n", cmd->right->token->value);
	// i gotta find the path that am a give to execve
	if (cmd->redirections)
	{
		t_redirection *current;
		current = cmd->redirections;
		while(current)
		{
			if (current->type == TOKEN_REDIR_OUT || current->type == TOKEN_REDIR_APPEND){
				dup2(current->fd, STDOUT_FILENO);
			}
			else if (current->type == TOKEN_REDIR_IN)
				dup2(current->fd, STDIN_FILENO);
			else if (current->type == TOKEN_HEREDOC){
				char *line;
                while ((line = readline("> ")) != NULL)
                {
					// printf("line :[%s]\n", line);
					// printf("delimiter: [%s]\n", current->delimiter);
                    if (ft_strcmp(line, current->delimiter) == 0)
                    {
                        free(line);
						// printf("shi l3iba\n");
                        break;
                    }
                    free(line);
                }
				close(current->fd);
				// printf("%s\n", current->file);
				int fd = open("/tmp/heredoc", O_RDONLY);
				dup2(fd, STDIN_FILENO);
				unlink("/tmp/heredoc");
				// close(fd);
			}
			current = current->next;
		}
	}
	path_dirs = ft_split(find_and_return_value(envps, "PATH"), ':');
	path = find_path(cmd->token->value, path_dirs);
	if (!path)
		exit(EXIT_FAILURE);
	// then iterate over the tree to get the set of args
	// tr9i3a ta yji wnswlo 3la fin kaystory envs
	args = examine(cmd->right, path, envps);
	env = to_arr(envps);
	execve(path, args, env);
	perror("command failed");
	exit(EXIT_FAILURE);
}

char	*find_path(char *file, char **arr)
{
	int		i;
	char	*path_buffer;

	if (!arr || !*arr)
		exit(EXIT_FAILURE);
	i = 0;
	path_buffer = NULL;
	while (arr[i])
	{
		if (access(file, X_OK | F_OK) == 0)
			return (ft_free(arr), ft_strdup(file));
		if (path_buffer)
			free_n_set_to_null(&path_buffer);
		path_buffer = malloc(ft_strlen(arr[i]) + ft_strlen(file) + 2);
		ft_strcpy(path_buffer, arr[i]);
		ft_strcat(path_buffer, "/");
		ft_strcat(path_buffer, file);
		if (access(path_buffer, X_OK) == 0)
			return (ft_free(arr), path_buffer);
		i++;
	}
	if (path_buffer)
		free(path_buffer);
	return (perror(file), ft_free(arr), NULL);
}
