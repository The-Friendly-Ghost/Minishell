/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:11:43 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/24 09:58:21 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdlib.h>

// lexer
char	**lexer(char *input);
char	**tokenizer(char *input, int token_count);

#endif
