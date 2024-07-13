/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:52:49 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/22 17:00:53 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*allocation(char const *s, char c)
{
	char	*word;
	int		word_len;

	word_len = 0;
	while (s[word_len] && s[word_len] != c)
		word_len++;
	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	word_len = 0;
	while (s[word_len] && s[word_len] != c)
	{
		word[word_len] = s[word_len];
		word_len++;
	}
	word[word_len] = '\0';
	return (word);
}

static char	**free_memory(char **result, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(result[j]);
		j++;
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	result = (char **)ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			result[i] = allocation(s, c);
			if (result[i] == NULL)
				return (free_memory(result, i));
			while (*s && *s != c)
				s++;
			i++;
		}
	}
	return (result);
}
/* 
int	main(void)
{
	char	**result;
	char	*str;
	char	delimiter;
	int		i;

	str = NULL;
	delimiter = 'c';
	i = 0;
	result = ft_split(str, delimiter);
	if (result == NULL)
	{
		printf("Input string is NULL\n");
		return (0);
	}
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	free_memory(result, i);
	return (0);
}
 */