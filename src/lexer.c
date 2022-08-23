/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 13:38:21 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/23 15:40:04 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include <stdlib.h>
#include <stdio.h>

// static void	set_space_after_quote(char *str, char *line, int *i, int *j)
// {
// 	line[*j] = str[*i];
// 	*i += 1;
// 	*j += 1;
// 	line[*j] = ' ';
// 	*j += 1;
// }

// static char	*set_whitespace(char *str, int w_spc)
// {
// 	char	first_quote;
// 	char	*line;
// 	int		i;
// 	int		j;

// 	first_quote = '0';
// 	i = 0;
// 	j = 0;
// 	if (w_spc)
// 	{
// 		line = NULL;
// 		line = ft_calloc(((int)ft_strlen(str) + w_spc) + 1, sizeof(line));
// 		if (!line)
// 			return (NULL);
// 		while (str[i])
// 		{
// 			if (first_quote == '0' && is_quote(str[i]))
// 				first_quote = str[i];
// 			if (in_string(str[i], false) && is_quote(str[i]) == first_quote)
// 			{
// 				set_space_after_quote(str, line, &i, &j);
// 				first_quote = '0';
// 			}
// 			else
// 			{
// 				line[j] = str[i];
// 				i++;
// 				j++;
// 			}
// 		}
// 		return (in_string(str[i], true), free(str), line);
// 	}
// 	return (in_string(str[i], true), str);
// }

// static char	**split_tokens(char *input)
// {
// 	char	**tokens;
// 	int		i;
// 	int		n;
// 	int		token_amount;

// 	i = 0;
// 	n = 0;
// 	if (!input)
// 		return (NULL);
// 	printf("input: %s\n", input);
// 	token_amount = count_tokens(input) + 1;
// 	tokens = ft_calloc((token_amount + 1), sizeof(*tokens));
// 	if (!tokens)
// 		return (free(input), NULL);
// 	while (input[i])
// 	{
// 		if (!ft_is_whitespace(input[i]))
// 		{
// 			if (!(get_tokens(tokens, (input + i), n, token_amount)))
// 				make_free(tokens, n);
// 			n++;
// 			if (is_quote(input[i]))
// 				skip_string(input, &i);
// 		}
// 		skip_token_and_whitespace(input, &i);
// 	}
// 	return (tokens);
// }

char	**lexer(char *input)
{
	int		i;
	char	**tokens;

	tokens = tokenizer(input);
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
	i = 0;
	return (tokens);
}
