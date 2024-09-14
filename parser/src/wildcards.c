/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:47:48 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/12 22:34:11 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

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

// char	**expand_wildcard(char *pattern)
// {
// 	DIR				*dir;
// 	struct dirent	*entry;
// 	char			**matches;
// 	char			**new_matches;
// 	int				size;
// 	int				i;

// 	size = 10;
// 	matches = malloc(sizeof(char *) * size);
// 	if (matches == NULL)
// 		return (NULL);
// 	dir = opendir(".");
// 	if (dir == NULL)
// 	{
// 		free(matches);
// 		return (NULL);
// 	}
// 	entry = readdir(dir);
// 	i = 0;
// 	while (entry != NULL)
// 	{
// 		if (match_pattern(pattern, entry->d_name))
// 		{
// 			if (i >= size)
// 			{
// 				size *= 2;
// 				new_matches = ft_realloc(matches, sizeof(char *) * size);
// 				if (new_matches == NULL)
// 				{
// 					perror("malloc");
// 					free_array(matches);
// 					closedir(dir);
// 					return (NULL);
// 				}
// 				matches = new_matches;
// 			}
// 			matches[i] = ft_strdup(entry->d_name);
// 			if (matches[i] == NULL)
// 			{
// 				perror("malloc");
// 				free_array(matches);
// 				closedir(dir);
// 				return (NULL);
// 			}
// 			i++;
// 		}
// 		entry = readdir(dir);
// 	}
// 	closedir(dir);
// 	if (i == 0)
// 	{
// 		free(matches);
// 		matches = NULL;
// 	}
// 	else
// 	{
// 		new_matches = ft_realloc(matches, sizeof(char *) * (i + 1));
// 		if (new_matches == NULL)
// 		{
// 			perror("malloc");
// 			free_array(matches);
// 			return (NULL);
// 		}
// 		matches = new_matches;
// 		matches[i] = NULL;
// 		sort_array(matches);
// 	}
// 	return (matches);
// }

int	resize_matches(char ***matches, int *size)
{
	char	**new_matches;

	*size *= 2;
	new_matches = ft_realloc(*matches, sizeof(char *) * (*size));
	if (!new_matches)
	{
		perror("malloc");
		free_array(*matches);
		return (0);
	}
	*matches = new_matches;
	return (1);
}

char	**find_matches_in_directory(DIR *dir, char *pattern, char **matches,
		int *i)
{
	struct dirent	*entry;
	char			*temp;
	int				size;

	size = 10;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (match_pattern(pattern, entry->d_name))
		{
			if (*i >= size && !resize_matches(&matches, &size))
				return (free_wildcards_on_error(matches, dir));
			temp = ft_strdup(entry->d_name);
			if (!temp)
				return (free_wildcards_on_error(matches, dir));
			matches[*i] = temp;
			(*i)++;
		}
		entry = readdir(dir);
	}
	return (matches);
}

char	**finalize_matches(char **matches, int i)
{
	char	**new_matches;

	if (i == 0)
	{
		free(matches);
		return (NULL);
	}
	new_matches = ft_realloc(matches, sizeof(char *) * (i + 1));
	if (!new_matches)
		return (free_wildcards_on_error(matches, NULL));
	matches = new_matches;
	matches[i] = NULL;
	sort_array(matches);
	return (matches);
}

char	**expand_wildcard(char *pattern)
{
	DIR		*dir;
	char	**matches;
	int		size;
	int		i;

	i = 0;
	size = 10;
	matches = malloc(sizeof(char *) * size);
	if (!matches)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (free_wildcards_on_error(matches, NULL));
	matches = find_matches_in_directory(dir, pattern, matches, &i);
	closedir(dir);
	return (finalize_matches(matches, i));
}
