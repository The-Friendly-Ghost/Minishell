/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 09:23:44 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/20 18:05:57 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H
# include "libft.h"
# include <stdbool.h>

// split tokens utils
int		len_wrds(const char *str);
char	*copy_on_dilim(const char *str, char *dst, int *i, char dilim);
char	*get_word(char **words, const char *str, int n, int total_words);
void	make_free(char **words, int n);
void	skip_word_and_whitespace(char *str, int *i);

// lexer utils
char	is_quote(char c);
int		count_whitespace(char *str);
bool	in_quotes(char c, bool reset);
void	skip_string(const char *str, int *i);
bool	in_quote(char s, char c);

#endif
