/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/20 21:34:39 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/20 23:04:22 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	char		*d;
// 	const char	*s;
// 	size_t		i;

// 	d = dst;
// 	s = src;
// 	i = 0;
// 	if (!dst && !src)
// 		return (0);
// 	while (n)
// 	{
// 		d[i] = s[i];
// 		i++;
// 		n--;
// 	}
// 	return (dst);
// }
// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }
// char	*ft_strdup(const char *s1)
// {
// 	void	*ptr;
// 	size_t	count;

// 	count = ft_strlen(s1) + 1;
// 	ptr = malloc(count * sizeof(char));
// 	if (!ptr)
// 		return (NULL);
// 	return (ft_memcpy(ptr, s1, count));
// }



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
	new_str = malloc((i * sizeof(char)) + 1);
	new_str = ft_memcpy(new_str, str, i);
	new_str[i + 1] = '\0';
	return (new_str);
}
