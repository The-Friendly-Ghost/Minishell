/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 09:23:44 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/17 16:50:51 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H
# include "libft.h"
# include <stdbool.h>

char	is_whitespace(char c);
char	is_quote(char c);
int		count_whitespace(char *str);
void	skip_string(const char *str, int *i);
bool	in_quote(char s, char c);
char	*set_whitespace(char *str, int w_spc);

#endif
