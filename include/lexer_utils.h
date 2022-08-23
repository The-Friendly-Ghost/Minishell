/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 09:23:44 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/23 15:34:28 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H
# include "libft.h"
# include <stdbool.h>

// split tokens utils
// int		count_tokens(char *str);
// char	*copy_on_dilim(const char *str, char *dst, int *i, char dilim);
// char	*get_tokens(char **tokens, char *input, int n, int total_tokens);
// void	make_free(char **tokens, int n);
// void	skip_token_and_whitespace(char *str, int *i);

// tokenizer utils
int		is_special(char *input, int i);
int		count_specials(char *input);
int		is_set(char c, const char *set);
int		count_whitespace(char *input, const char *set);

// lexer utils
char	is_quote(char c);
bool	in_string(char c, bool reset);
void	skip_string(const char *str, int *i);
bool	in_quote(char s, char c);
char	*set_whitespace(char *str, int specials_count);

// tokenizer
char	**tokenizer(char *input);

#endif
