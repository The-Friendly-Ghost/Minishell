/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 14:47:06 by pniezen       #+#    #+#                 */
/*   Updated: 2021/10/20 17:30:56 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	find_set(char s1, char const *set)
{
	while (*set)
	{
		if (s1 == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	end;

	if (!s1 | !set)
		return (NULL);
	while (find_set(*s1, set))
		s1++;
	if (*s1 == '\0')
		return (ft_strdup(""));
	end = (ft_strlen(s1));
	while (find_set(s1[end - 1], set))
		end--;
	str = malloc(end + 1 * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, end + 1);
	return (str);
}
