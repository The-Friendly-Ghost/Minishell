/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_destroy.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:19:55 by cpost         #+#    #+#                 */
/*   Updated: 2022/09/05 13:45:35 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Receives the 2D token array (with all the tokens in it) and
 * destroys it.
 * @param **tokens A pointer to a 2D-array with the tokens in it
 * @return Nothing 
 * @note
 */
void	destroy_token_array(char **token_array)
{
	unsigned int	i;

	i = 0;
	if (token_array)
	{
		while (token_array[i])
		{
			if (token_array[i])
				free(token_array[i]);
			i++;
		}
		free(token_array);
	}
}

/**
 * @brief Receives a pointer to the linked list with tokens
 * and then frees all the structs in it one by one.
 * @param **tokens A pointer to the linked list with tokens
 * @return Nothing 
 * @note
 */
void	destroy_token_list(t_token **token_list)
{
	t_token	*temp;
	t_token	*free_temp;

	if (*token_list)
	{
		temp = *token_list;
		while (temp)
		{
			free_temp = temp;
			free(temp->content);
			temp = temp->next;
			free(free_temp);
		}
		free(token_list);
	}
}