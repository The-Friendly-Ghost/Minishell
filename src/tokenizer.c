/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 10:34:47 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/23 15:41:14 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include <stdlib.h>
#include <stdio.h>

char	**tokenizer(char *input)
{
	const char	set[] = " \t\n\v\f\r";
	char		*line;
	int			specials_count;
	int			w_spc;
	int			tn;

	if (!input)
		return (NULL);
	w_spc = count_whitespace(input, set);
	tn = w_spc + 1;
	specials_count = count_specials(input);
	line = set_whitespace(input, specials_count);
	if (!line)
		return (NULL);
	printf("%s;\n", line);
	printf("count_specials: %i\n", specials_count);
	printf("count_whitespace: %i\n", w_spc);
	printf("count_token: %i\n", tn);
	return (ft_split(line, ' '));
}
