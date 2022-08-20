/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 13:38:21 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/20 18:11:14 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include <stdio.h>

static void	copy_str_and_whitespace(char *str, char *line, int *i, int *j)
{
	line[*j] = ' ';
	*j += 1;
	line[*j] = str[*i];
	*i += 1;
	*j += 1;
}

static char	*set_whitespace(char *str, int w_spc)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = NULL;
	line = ft_calloc(((int)ft_strlen(str) + w_spc) + 1, sizeof(line));
	if (!line)
		return (NULL);
	while (str[i])
	{
		if (!in_quotes(str[i], false) && str[i] == is_quote(str[i]) \
		&& !ft_is_whitespace(str[i]))
			copy_str_and_whitespace(str, line, &i, &j);
		if (in_quotes(str[i], false) && str[i] == is_quote(str[i]) \
		&& str[i + 1] != '\0' && !ft_is_whitespace(str[0]))
			copy_str_and_whitespace(str, line, &i, &j);
		line[j] = str[i];
		i++;
		j++;
	}
	printf("%s\n%s\n", str, line);
	free(str);
	return (line);
}

static char	**split_tokens(char *input)
{
	char	**words;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (!input)
		return (NULL);
	words = ft_calloc((len_wrds(input) + 1), sizeof(*words));
	if (!words)
		return (free(input), NULL);
	while (input[i])
	{
		if (!ft_is_whitespace(input[i]))
		{
			if (!(get_word(words, (input + i), n, len_wrds(input))))
				make_free(words, n);
			n++;
			if (is_quote(input[i]))
				skip_string(input, &i);
		}
		skip_word_and_whitespace(input, &i);
	}
	return (free(input), words);
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
