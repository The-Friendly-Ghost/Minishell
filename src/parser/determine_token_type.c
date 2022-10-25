/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   determine_token_type.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:54:42 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/24 11:16:27 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Determines if the token starts with a dollar sign. If so, then
 * it checks:
 * 1. if the next character is a question mark. If so, the token is a
 * 'print_exit_code' token.
 * 2. if there is a character after the dollar sign. If so, the token
 * is a environement variable.
 * 3. if there is no character after the dollar sign, return 0.
 * @param *token A pointer to a char * (the token)
 * @return The corresponding int for the token type, or 0 if no match
 * is found.
 * @note -
 */
static int	check_if_token_starts_with_dollar_sign(char *token,
	t_token_type *token_type)
{
	if (ft_strcmp(token, "$?") == 0)
		*token_type = print_exit_code;
	else if (token[0] == '$' && token[1])
		*token_type = enviroment_variable;
	return (*token_type);
}

/**
 * @brief Determines if the token is a redirect and returns a corresponding
 * token_type number or 0 if no match is found.
 * @param *token A pointer to a char * (the token)
 * @return int 
 * @note -
 */
static int	check_if_token_is_redirection(char *token, t_token_type *token_type)
{
	if (ft_strcmp(token, "<") == 0)
		*token_type = redirect_input;
	else if (ft_strcmp(token, ">") == 0)
		*token_type = redirect_output;
	else if (ft_strcmp(token, "<<") == 0)
		*token_type = delimiter;
	else if (ft_strcmp(token, ">>") == 0)
		*token_type = redirect_output_append;
	return (*token_type);
}

/**
 * @brief Determines if the token is a builtin function and returns
 * a corresponding number or 0 if no match is found.
 * @param *token A pointer to a char * (the token)
 * @return int 
 * @note -
 */
static int	check_if_token_is_builtin(char *token, t_token_type *token_type)
{
	if (ft_strcmp(token, "echo") == 0)
		*token_type = echo;
	else if (ft_strcmp(token, "cd") == 0)
		*token_type = cd;
	else if (ft_strcmp(token, "pwd") == 0)
		*token_type = pwd;
	else if (ft_strcmp(token, "export") == 0)
		*token_type = export_var;
	else if (ft_strcmp(token, "unset") == 0)
		*token_type = unset;
	else if (ft_strcmp(token, "env") == 0)
		*token_type = env;
	else if (ft_strcmp(token, "exit") == 0)
		*token_type = exit_program;
	return (*token_type);
}

/**
 * @brief Identifies the type of the token given as a paramater. The
 * corresponding token_type number will be returned.
 * @param *token A pointer to a char * (the token)
 * @return int 
 * @note -
 */
int	determine_token_type(char *token)
{
	t_token_type	token_type;

	token_type = invalid_input;
	if (check_if_token_is_builtin(token, &token_type))
		return (token_type);
	if (check_if_token_is_redirection(token, &token_type))
		return (token_type);
	if (check_if_token_starts_with_dollar_sign(token, &token_type))
		return (token_type);
	if (ft_strcmp(token, "|") == 0)
		return (is_pipe);
	return (string);
}
