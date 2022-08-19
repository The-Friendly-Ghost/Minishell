/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   determine_token_type.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:54:42 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/18 15:32:31 by cpost         ########   odam.nl         */
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
static unsigned int	check_if_token_starts_with_dollar_sign(char *token,
	int *token_type)
{
	*token_type = 0;
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
static unsigned int	check_if_token_is_redirection(char *token, int *token_type)
{
	*token_type = 0;
	if (ft_strcmp(token, "<") == 0)
		*token_type = redirect_input;
	if (ft_strcmp(token, ">") == 0)
		*token_type = redirect_output;
	if (ft_strcmp(token, "<<") == 0)
		*token_type = delimiter;
	if (ft_strcmp(token, ">>") == 0)
		*token_type = redirect_output_append;
	return (*token_type);
}

/**
 * @brief Determines if the token is a string with single or double 
 * quotation mark sand returns a corresponding token_type number or 0
 * if no match is found.
 * @param *token A pointer to a char * (the token)
 * @return int 
 * @note -
 */
static unsigned int	check_if_token_is_string(char *token, int *token_type)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	*token_type = 0;
	len = ft_strlen(token);
	if (len > 2)
	{
		if (token[0] == '"' && token[len - 1] == '"')
			*token_type = string_double_quote;
		if (token[0] == '\'' && token[len - 1] == '\'')
			*token_type = string_single_quote;
	}
	return (*token_type);
}

/**
 * @brief Determines if the token is a builtin function and returns
 * a corresponding number or 0 if no match is found.
 * @param *token A pointer to a char * (the token)
 * @return int 
 * @note -
 */
static unsigned int	check_if_token_is_builtin(char *token, int *token_type)
{
	*token_type = 0;
	if (ft_strcmp(token, "echo") == 0)
		*token_type = echo;
	if (ft_strcmp(token, "cd") == 0)
		*token_type = cd;
	if (ft_strcmp(token, "pwd") == 0)
		*token_type = pwd;
	if (ft_strcmp(token, "export") == 0)
		*token_type = export;
	if (ft_strcmp(token, "unset") == 0)
		*token_type = unset;
	if (ft_strcmp(token, "env") == 0)
		*token_type = env;
	if (ft_strcmp(token, "exit") == 0)
		*token_type = exit_program;
	return (*token_type);
}

/**
 * @brief Identifies the type of the token given as a paramater. Then a
 * corresponding token_type number gets returned.
 * @param *token A pointer to a char * (the token)
 * @return Unsigned int 
 * @note -
 */
unsigned int	determine_token_type(char *token)
{
	int	token_type;

	if (check_if_token_is_builtin(token, &token_type) != 0)
		return (token_type);
	if (check_if_token_is_string(token, &token_type) != 0)
		return (token_type);
	if (check_if_token_is_redirection(token, &token_type) != 0)
		return (token_type);
	if (check_if_token_starts_with_dollar_sign(token, &token_type) != 0)
		return (token_type);
	if (ft_strcmp(token, "|") == 0)
		return (pipe);
	return (string_without_quote);
}
