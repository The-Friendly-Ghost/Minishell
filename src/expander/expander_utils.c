/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 17:49:46 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/03 14:52:44 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief A custom strjoin for minishell. 
 * @param s1 Source string
 * @param s2 The string that has to be joined to the source string.
 * @return The newly formed combined string.
 * @note
 */
static char	*ft_strjoin_alt(char *s1, char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	if (!s2)
		s2_len = 0;
	else
		s2_len = ft_strlen(s2);
	str = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_len + 1);
	ft_strlcat(str, s2, (s1_len + s2_len + 1));
	free(s1);
	return (str);
}

/**
 * @brief The ft_strdup_before_size function creates a new string from the
 * source string (str) up to position 'size'.
 * @param str the source string
 * @param c The character to look for
 * @return *char - a new string copied up to size.
 * @note
 */
static char	*ft_strdup_before_size(const char *str, int size)
{
	int		i;
	char	*new_str;

	i = 0;
	if (size == 0)
		return (NULL);
	while (str[i] && i < size)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	new_str = malloc((i * sizeof(char)) + 1);
	new_str = ft_memcpy(new_str, str, i);
	new_str[i] = '\0';
	return (new_str);
}

/**
 * @brief Identifies the portion of the string after the dollar sign that
 * qualifies as the environment variable.
 * @param str The content of the token.
 * @return returns a new string that is the environment variable. 
 * @note This function does not check if the environment variable is valid.
 */
char	*id_env_var(char *str)
{
	int		i;
	char	*env_var;

	i = 0;
	while (str[i] && str[i] != '"' && str[i] != '\''
		&& !ft_is_whitespace(str[i]))
	{
		if (i > 0 && str[i] == '$')
			break ;
		else
			i++;
	}
	env_var = malloc(sizeof(char) * (i + 1));
	env_var[i] = '\0';
	i--;
	while (i >= 0)
	{
		env_var[i] = str[i];
		i--;
	}
	return (env_var);
}

/**
 * @brief Identifies the portion of the string after the dollar sign that
 * qualifies as the environment variable.
 * @param str The content of the token.
 * @return returns a new string that is the environment variable. 
 * @note This function does not check if the environment variable is valid.
 */
char	*expand_env_var(char *name, char *value, char *str, unsigned int i)
{
	char	*str_before;
	char	*str_after;
	char	*expanded_str;

	str_before = ft_strdup_before_size(str, i);
	str_after = ft_strdup(str + (i + ft_strlen(name)));
	if (str_before == NULL)
		expanded_str = ft_strdup(value);
	else
		expanded_str = ft_strjoin_alt(str_before, value);
	if (str_after != NULL)
		expanded_str = ft_strjoin(expanded_str, str_after);
	return (expanded_str);
}
