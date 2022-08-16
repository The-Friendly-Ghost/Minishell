/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 10:08:03 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/16 12:08:01 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	len_wrds(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (count);
}

static char	*find_word(char **words, const char *s, char c, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	str = malloc((i + 1) * sizeof(char));
	i = 0;
	while (s[i] != c && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	words[n] = str;
	return (*words);
}

static void	make_free(char **words, size_t n)
{
	while (n > 0)
		free(words[n]);
	n--;
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (!s)
		return (NULL);
	words = ft_calloc((len_wrds(s, c) + 1), sizeof(*words));
	if (!words)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!(find_word(words, (s + i), c, n)))
				make_free(words, n);
			n++;
		}
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (words);
}
