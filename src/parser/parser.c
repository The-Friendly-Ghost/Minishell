/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 14:15:09 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/16 15:52:43 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Receives a 2D array with all the tokens in it. (The tokens have been
 * trimmed by the lexer.) Parser then puts all the tokens inside of a linked
 * list and attaches relevant information to it.
 * @param **tokens A pointer to a 2D-array with the tokens in it
 * @return A pointer to a linked list or NULL if the creation of the linked
 * list failed. 
 * @note -
 */
t_token	*parser(char **tokens)
{
	t_token	*token;

	token = NULL;
	return (token);
}
