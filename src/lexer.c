/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 13:38:21 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/24 11:50:12 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include <stdlib.h>
#include <stdio.h>

static void	add_space(char *line, char *str, int *i, int *j)
{
	if (is_special(str, *i) == 1)
	{
		line[*j] = ' ';
		*j += 1;
		line[*j] = str[*i];
		*j += 1;
		*i += 1;
		line[*j] = ' ';
		*j += 1;
	}
	if (is_special(str, *i) == 2)
	{
		line[*j] = ' ';
		*j += 1;
		line[*j] = str[*i];
		*j += 1;
		*i += 1;
		line[*j] = str[*i];
		*j += 1;
		*i += 1;
		line[*j] = ' ';
		*j += 1;
	}
}

static char	*set_whitespace(char *str, int specials_count)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = ft_calloc((ft_strlen(str) + specials_count) + 1, sizeof(line));
	if (!line)
		return (NULL);
	while (str[i])
	{
		if (is_special(str, i))
			add_space(line, str, &i, &j);
		line[j] = str[i];
		j++;
		i++;
	}
	return (line);
}

char	**lexer(char *input)
{
	const char	set[] = " \t\n\v\f\r";
	int			i;
	int			token_count;
	char		*line;
	char		**tokens;

	line = set_whitespace(input, count_specials(input));
	if (!line)
		return (NULL);
	token_count = count_whitespace(line, set) + 1;
	printf("token_count: %i\n", token_count);
	tokens = tokenizer(line, token_count);
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
	return (free(line), tokens);
}
