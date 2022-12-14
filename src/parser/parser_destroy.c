/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_destroy.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:19:55 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/21 08:28:38 by pniezen       ########   odam.nl         */
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
void	destroy_double_array(char **token_array)
{
	unsigned int	i;

	i = 0;
	if (!token_array)
		return ;
	while (token_array[i])
	{
		free(token_array[i]);
		i++;
	}
	free(token_array);
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
	t_token	*previous_node;

	if (!*token_list)
		return ;
	temp = *token_list;
	while (temp)
	{
		if (temp->heredoc_file)
		{
			unlink(temp->heredoc_file);
			free(temp->heredoc_file);
			temp->heredoc_file = NULL;
		}
		previous_node = temp;
		free(temp->content);
		temp = temp->next;
		free(previous_node);
	}
	*token_list = NULL;
}

/**
 * @brief Receives a pointer to the linked list with tokens
 * and then frees all the structs in it one by one.
 * @param **tokens A pointer to the linked list with tokens
 * @return Nothing 
 * @note
 */
void	destroy_env_list(t_env **env_list)
{
	t_env	*temp;
	t_env	*previous_node;

	if (*env_list)
	{
		temp = *env_list;
		while (temp)
		{
			previous_node = temp;
			free(temp->var_name);
			free(temp->value);
			temp = temp->next;
			free(previous_node);
		}
		*env_list = NULL;
	}
}
