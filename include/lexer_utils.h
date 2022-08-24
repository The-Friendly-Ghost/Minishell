/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 09:23:44 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/24 10:11:15 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H
# include "libft.h"
# include <stdbool.h>

// tokenizer utils
int		is_set(char c, const char *set);
int		count_whitespace(char *input, const char *set);
int		is_special(char *input, int i);
int		count_specials(char *input);

// lexer utils
char	is_quote(char c);
bool	in_string(char c, bool reset);
void	skip_string(const char *str, int *i);

#endif
