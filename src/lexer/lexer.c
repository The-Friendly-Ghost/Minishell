/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 13:44:35 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/23 17:26:19 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * @param 
 * @return 
 * @note -
 */
char	*ft_strldup(char *input, int size)
{
	char			*new_token;
	unsigned int	i;

	i = 0;
	new_token = malloc(size + 1);
	if (!new_token)
		return (NULL);
	while (i < size)
	{
		new_token[i] = input[i];
		i++;
	}
	new_token[i] = '\0';
	return (new_token);
}

/**
 * @brief 
 * @param 
 * @return 
 * @note -
 */
char	*make_redirect_token(char *input, char c, int *i)
{
	unsigned int	size;
	char			*new_token;

	size = 1;
	if (input[*i + 1] == c)
	{
		*i += 1;
		size++;
	}
	new_token = ft_strldup(&input[*i], size);
	*i += 1;
	return (new_token);
}

/**
 * @brief 
 * @param 
 * @return 
 * @note -
 */
char	*make_pipe_token(char *input, char c, int *i)
{
	char	*new_token;

	new_token = ft_strldup(&input[*i], 1);
	*i += 1;
	return (new_token);
}

/**
 * @brief 
 * @param 
 * @return 
 * @note -
 */
char	*make_string_token(char *input, char c, int *i, unsigned int size)
{
	//printf("char = [%c], input = %s\n", c, input);
	while (input[*i] != c || (c != '\0' && (input[*i] != '"'
				|| input[*i] != '\'' || ft_is_whitespace(input[*i])
				|| input[*i] == '|' || input[*i] == '<' || input[*i] == '>')))
	{
	printf("[%d]\n", *i);
		printf("HIER KOMEN WE\n");
		*i += 1;
		size++;
	}
	*i += 1;
	size++;
	if (input[*i] == '\0' || ft_is_whitespace(input[*i]) || input[*i] == '|'
		|| input[*i] == '<' || input[*i] == '>')
		return (ft_strldup(&input[*i - size], size));
	else if (input[*i] == '"' || input[*i] == '\'')
	{
		*i += 1;
		size++;
		make_string_token(input, input[*i], i, size);
	}
	else
		make_string_token(input, '\0', i, size);
}

/**
 * @brief 
 * @param 
 * @return 
 * @note -
 */
char	*get_next_token(char *input, int *i)
{
	char	c;

	if (input[*i] == '"' || input[*i] == '\'')
	{
		//printf("char = [%c], input = %s\n", c, input);
		c = input[*i];
		*i += 1;
		return (make_string_token(input, c, i, 1));
	}
	else if (input[*i] == '|')
		return (make_pipe_token(input, input[*i], i));
	else if (input[*i] == '>' || input[*i] == '<')
		return (make_redirect_token(input, input[*i], i));
	else
	{
		printf("char = [%c], input = %s\n", c, input);
		return (make_string_token(input, '\0', i, 0));
	}
}
