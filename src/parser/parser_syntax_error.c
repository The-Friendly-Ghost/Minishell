/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_syntax_error.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 17:22:09 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/24 20:09:38 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Because it's annoying to make too long if statements, I put this if
 * statement in a seperate function. 
 * @param type The type that we have to check
 * @return True if type is a redirect, otherwise false.
 * @note
 */
bool	is_redirect(unsigned int type)
{
	if (type == redirect_input || type == redirect_output
		|| type == redirect_output_append || type == delimiter)
		return (true);
	else
		return (false);
}

/**
 * @brief Prints an error message and always returns true
 * @param *print_code The print_code of the error message that has to be
 * printed
 * @return Always true
 * @note
 */
bool	print_syntax_error(int *print_code)
{
	if (*print_code == newline_error)
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
	else if (*print_code == redirect_error_input)
		ft_putendl_fd("minishell: syntax error near unexpected token `<'", 2);
	else if (*print_code == redirect_error_output)
		ft_putendl_fd("minishell: syntax error near unexpected token `>'", 2);
	else if (*print_code == delimiter_error)
		ft_putendl_fd("minishell: syntax error near unexpected token `<<'", 2);
	else if (*print_code == redirect_append_error)
		ft_putendl_fd("minishell: syntax error near unexpected token `>>'", 2);
	else if (*print_code == pipe_error)
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
	return (true);
}

/**
 * @brief Child function of check_for_syntax_errors.
 * @param *token The token to check
 * @return true if syntax error is found. False if no error found.
 * @note Bash only looks at the token in front for syntax error checking.
 */
static int	check_pipe_error(t_token *token, int *print_code)
{
	t_token			*temp;

	temp = token;
	if (temp->previous == NULL)
		*print_code = pipe_error;
	else if (temp->previous->type == is_pipe
		|| is_redirect(temp->previous->type))
		*print_code = pipe_error;
	return (*print_code);
}

/**
 * @brief Child function of check_for_syntax_errors.
 * @param **token_list A linked list with all the tokens in it.
 * @return true if syntax error is found. False if no error found.
 * @note Bash only looks at the token in front for syntax error checking.
 */
static int	check_redirect_error(t_token *token, int *print_code)
{
	t_token			*temp;

	temp = token;
	if (temp->previous != NULL && is_redirect(temp->previous->type))
		*print_code = temp->type;
	else if (temp->next == NULL)
		*print_code = newline_error;
	return (*print_code);
}

/**
 * @brief Function that checks for syntax errors.
 * @param **token_list A linked list with all the tokens in it.
 * @return true if syntax error is found. False if no error found.
 * @note
 */
bool	check_for_syntax_error(t_token **token_list)
{
	t_token	*temp;
	int		print_code;

	temp = *token_list;
	print_code = 0;
	while (temp)
	{
		if (temp->type == is_pipe && check_pipe_error(temp, &print_code))
			return (print_syntax_error(&print_code));
		if (is_redirect(temp->type) && check_redirect_error(temp, &print_code))
			return (print_syntax_error(&print_code));
		temp = temp->next;
	}
	return (false);
}
