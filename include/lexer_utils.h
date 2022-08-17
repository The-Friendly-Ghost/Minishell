/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 09:23:44 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/17 15:02:15 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H
# include "libft.h"

char	is_whitespace(char c);
char	is_quote(char c);
int		count_whitespace(char *str);
void	skip_string(const char *str, int *i);
char	*set_whitespace(char *str, int w_spc);

#endif
