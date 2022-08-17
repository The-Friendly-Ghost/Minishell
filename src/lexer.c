/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 13:38:21 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/17 16:39:08 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include <stdio.h>

static int	len_wrds(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			count++;
		while (!is_whitespace(str[i]) && str[i])
			i++;
		while (is_whitespace(str[i]) && str[i])
			i++;
	}
	return (count);
}

static char	*find_word(char **words, const char *str, int n)
{
	char	*dst;
	char	dilim;
	int		i;

	i = 0;
	while (!is_whitespace(str[i]) && str[i])
		i++;
	dst = malloc((i + 1) * sizeof(char));
	i = 0;
	dilim = is_quote(str[i]);
	if (dilim)
	{
		dst[i] = dilim;
		i++;
		while (str[i] != dilim)
		{
			dst[i] = str[i];
			i++;
		}
		dst[i] = dilim;
		dst[i + 1] = '\0';
		words[n] = dst;
		return (*words);
	}
	while (!is_whitespace(str[i]) && str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	words[n] = dst;
	return (*words);
}

static void	make_free(char **words, int n)
{
	while (n > 0)
		free(words[n]);
	n--;
}

static char	**split_tokens(char const *str)
{
	char	**words;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (!str)
		return (NULL);
	words = ft_calloc((len_wrds(str) + 1), sizeof(*words));
	if (!words)
		return (NULL);
	while (str[i])
	{
		if (!is_whitespace(str[i]))
		{
			if (!(find_word(words, (str + i), n)))
				make_free(words, n);
			n++;
			if (is_quote(str[i]))
				skip_string(str, &i);
		}
		while (!is_whitespace(str[i]) && str[i])
			i++;
		while (is_whitespace(str[i]) && str[i])
			i++;
	}
	return (words);
}

char	**lexer(char *input)
{
	int		i;
	int		w_spc;
	char	**tokens;

	w_spc = count_whitespace(input);
	tokens = split_tokens(set_whitespace(input, w_spc));
	if (!tokens)
		exit(EXIT_FAILURE);
	i = 0;
	printf("tokens: ");
	while (tokens[i])
	{
		printf("[%s] ", tokens[i]);
		i++;
	}
	printf("\n");
	return (tokens);
}
