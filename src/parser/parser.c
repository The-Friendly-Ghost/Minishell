/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 14:15:09 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/26 14:48:55 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a linked list element for a single token and adds
 * it to the token_list.
 * @param *token A pointer to a char * (the token)
 * @return Nothing
 * @note -
 */
static void	add_new_element_to_token_list(t_token **token_list,
			t_token *new_element)
{
	t_token	*temp;

	if (!*token_list)
		*token_list = new_element;
	else
	{
		temp = *token_list;
		while (temp->next)
			temp = temp->next;
		new_element->previous = temp;
		temp->next = new_element;
	}
}

/**
 * @brief Creates a struct for a single token.
 * @param *token A pointer to a char * (the token)
 * @return *t_token (pointer to the new token element) 
 * @note determine_token_type can be found in determine_token_type.c
 */
static t_token	*create_new_element(char *token, int id)
{
	t_token				*new_element;
	static t_token_type	temp_type;
	static int			cur;

	new_element = malloc(sizeof(t_token));
	if (!new_element)
		return (NULL);
	new_element->id = id;
	new_element->content = ft_strdup(token);
	if (!new_element->content)
		return (free(new_element), NULL);
	new_element->next = NULL;
	new_element->previous = NULL;
	if (cur == (id - 1) && (temp_type == infile || temp_type == outfile
			|| temp_type == is_heredoc))
	{
		new_element->type = temp_type;
		temp_type = 0;
	}
	else
	{
		new_element->type = determine_token_type(token);
		if (new_element->type == redirect_input)
			temp_type = infile;
		else if (new_element->type == redirect_output)
			temp_type = outfile;
		else if (new_element->type == redirect_output_append)
			temp_type = outfile;
		else if (new_element->type == delimiter)
			temp_type = is_heredoc;
	}
	cur = id;
	return (new_element);
}

/**
 * @brief Receives a 2D array with all the tokens in it. Returns A pointer 
 * to a linked list or NULL if the creation of the linked list failed. 
 * @param **tokens A pointer to a 2D-array with the tokens in it
 * @return **token_list - Pointer to the first element of the linked list 
 * @note Destroy functions can be found in parser_destroy.c
 */
bool	parser(char **token_array, t_token **token_list)
{
	t_token	*new_element;
	int		i;

	i = 0;
	while (token_array[i])
	{
		new_element = create_new_element(token_array[i], i);
		if (!new_element)
		{
			err_msg(NULL, NULL, NULL);
			destroy_double_array(token_array);
			return (destroy_token_list(token_list), false);
		}
		add_new_element_to_token_list(token_list, new_element);
		i++;
	}
	if (check_for_syntax_error(*token_list))
		return (destroy_token_list(token_list), false);
	return (true);
}
