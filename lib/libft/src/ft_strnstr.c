/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 16:35:03 by pniezen       #+#    #+#                 */
/*   Updated: 2021/10/27 17:37:20 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	if (*needle == '\0')
		return ((char *) haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[l])
		{
			while (needle[l] != '\0' && haystack[i + l] == needle[l]
				&& (i + l) < len)
				l++;
			if (needle[l] == '\0')
				return ((char *) &haystack[i]);
		}
		i++;
		l = 0;
	}
	return (0);
}
