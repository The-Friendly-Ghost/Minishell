/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 14:15:09 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/31 12:55:34 by cpost         ########   odam.nl         */
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
 * @brief Checks if a token is a pipe or a redirect.
 * @param *token A pointer to a char * (the token)
 * @return True if token is a pipe or redirect. False if not.
 * @note
 */
static bool	is_pipe_or_redirect(char *token)
{
	if (!ft_strcmp(token, "|"))
		return (true);
	if (!ft_strcmp(token, ">"))
		return (true);
	if (!ft_strcmp(token, "<"))
		return (true);
	if (!ft_strcmp(token, ">>"))
		return (true);
	if (!ft_strcmp(token, "<<"))
		return (true);
	return (false);
}

static void	get_token_type(t_token *new, t_token_type *temp_type, int cur,
		int id)
{
	if (cur == (id - 1) && (*temp_type == infile || *temp_type == outfile)
		&& !is_pipe_or_redirect(new->content))
	{
		new->type = *temp_type;
		*temp_type = 0;
	}
	else
	{
		new->type = determine_token_type(new->content);
		if (*temp_type == infile || *temp_type == outfile)
			*temp_type = 0;
		if (new->type == redirect_input)
			*temp_type = infile;
		else if (new->type == redirect_output
			|| new->type == redirect_output_append)
			*temp_type = outfile;
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
	t_token				*new;
	static t_token_type	temp_type;
	static int			cur;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->id = id;
	new->content = ft_strdup(token);
	if (!new->content)
		return (free(new), NULL);
	new->heredoc_file = NULL;
	new->next = NULL;
	new->previous = NULL;
	get_token_type(new, &temp_type, cur, id);
	cur = id;
	return (new);
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
			printf("Error Parser Linked List Creation\n");
			destroy_double_array(token_array);
			return (destroy_token_list(token_list), false);
		}
		add_new_element_to_token_list(token_list, new_element);
		i++;
	}
	// destroy_double_array(token_array);
	if (check_for_syntax_error(*token_list))
		return (destroy_token_list(token_list), false);
	expand_heredocs(*token_list);
// print_token_list(*token_list);
	return (true);
}
