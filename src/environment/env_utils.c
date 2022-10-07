/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/20 21:34:39 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/07 14:29:59 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief checks if the source string (str) contains a character after
 * the first '=' character.
 * @param str The source string
 * @param c The character to check for
 * @return True if there is a character after the '='. False if
 * there is a '\0' after the '='.
 * found within the source string.
 * @note
 */
bool	check_if_env_has_value(const char *str)
{
	unsigned long	i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (str[i + 1] == '\0')
		return (false);
	else
		return (true);
}

/**
 * @brief The ft_strdup_after_char() searches for the first occurrence of 
 * the character c. It then creates a new string from the position of c + 1.
 * @param str the source string
 * @param c ascii value of the character to search for
 * @return *char - new string. If characther is
 * 0, return NULL. If c isn't found, return NULL.
 * @note
 */
char	*ft_strdup_after_char(const char *str, char c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (ft_strdup(&str[i + 1]));
		i++;
	}
	return (NULL);
}

/**
 * @brief The ft_strdup_before_char() function finds the first occurrence of char
 * c. It then creates a new string and copies up to char c to this new string
 * and puts a \0 after it. Note, char C is not copied. if c is \0, return a
 * copy of str. If c isn't found, return NULL;
 * @param str the source string
 * @param c ascii value of the character to search for
 * @return *char - a new string copied up to char c. If characther is
 * 0, return the end of the string.
 * @note
 */
char	*ft_strdup_before_char(const char *str, char c)
{
	int		i;
	char	*new_str;

	i = 0;
	if (c == '\0')
		return (ft_strdup(str));
	while (str[i] != c)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	new_str = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(new_str, str, i + 1);
	return (new_str);
}

/**
 * @brief searches for the environment string pointed to by name and 
 * returns the associated value to the string.
 * @param name This is the C string containing the name of the 
 * requested variable.
 * @return This function returns a null-terminated string with the 
 * value of the requested environment variable, or NULL if that environment 
 * variable does not exist.
 * @note
 */
char	*ft_getenv(const char *name)
{
	t_env		**env;
	t_env		*temp;

	if (name == NULL)
		return (NULL);
	env = get_env_list();
	if (!(*env))
		return (NULL);
	else
		temp = *env;
	while (temp->next)
	{
		if (ft_strcmp(temp->var_name, name) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	set_exit_code(int exit_code)
{
	t_program	*program;

	program = get_program();
	program->exit_code = exit_code;
}
