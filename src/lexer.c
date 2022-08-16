/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 13:38:21 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/16 15:21:21 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	**lexer(char *input)
{
	int		i;
	char	**tokens;
	char	*quotes;

	quotes = ft_strchr(input, '\"');
	if (quotes && !ft_strchr(quotes, '\"'))
		exit(EXIT_FAILURE);
	tokens = ft_split(input, ' ');
	if (!tokens)
		exit(EXIT_FAILURE);
	i = 0;
	while (tokens[i])
	{
		printf("%s", tokens[i]);
		i++;
	}
	return (tokens);
}
