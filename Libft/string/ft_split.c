/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:57:44 by thmouty           #+#    #+#             */
/*   Updated: 2024/04/24 18:57:44 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

char	**free_all_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static char	*alloc_word(const char *s, int start, int finish)
{
	char	*word;
	int		i;

	word = (char *)ft_calloc((finish - start + 1), sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < finish)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		start;
	int		word_index;
	char	**result;

	result = (char **)ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	word_index = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			result[word_index] = alloc_word(s, start, i);
			if (!result[word_index++])
				return (free_all_split(result));
		}
	}
	return (result);
}
