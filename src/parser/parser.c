/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 14:15:09 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/18 14:12:09 by cpost         ########   odam.nl         */
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
static t_token	*create_new_element(char *token, unsigned int id)
{
	t_token	*new_element;

	new_element = malloc(sizeof(t_token));
	if (!new_element)
		return (NULL);
	new_element->id = id;
	new_element->content = token;
	new_element->next = NULL;
	new_element->previous = NULL;
	new_element->type = determine_token_type(token);
}

/**
 * @brief Determines the amount of tokens inside of the token array
 * @param **tokens A pointer to a 2D-array with the tokens in it
 * @return Unsigned int
 * @note -
 */
static unsigned int	get_token_count(char **token_array)
{
	int	i;

	i = 0;
	while (token_array[i])
		i++;
	return (i);
}

/**
 * @brief Receives a 2D array with all the tokens in it. Returns A pointer 
 * to a linked list or NULL if the creation of the linked list failed. 
 * @param **tokens A pointer to a 2D-array with the tokens in it
 * @return **token_list - Pointer to the first element of the linked list 
 * @note Destroy functions can be found in parser_destroy.c
 */
t_token	**parser(char **token_array)
{
	t_token			**token_list;
	t_token			*new_element;
	unsigned int	token_count;
	unsigned int	i;

	token_count = get_token_count(token_array);
	//if (token_count == 0)
		//error_function
	//*token_list = create_new_element(token_array[0], 0);
	i = 0;
	while (i < token_count)
	{
		new_element = create_new_element(token_array[i], i);
		if (new_element == NULL)
		{
			ft_printf("Error Parser Linked List Creation\n");
			destroy_token_array(token_array);
			destroy_token_list(token_list);
			return (NULL);
		}
		add_new_element_to_token_list(token_list, new_element);
	}
	destroy_token_array(token_array);
	return (token_list);
}
