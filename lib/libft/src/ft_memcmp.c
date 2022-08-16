/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 16:34:24 by pniezen       #+#    #+#                 */
/*   Updated: 2021/10/27 17:34:25 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = s1;
	str2 = s2;
	if (!str1 && !str2)
		return (0);
	while (n > 0)
	{
		if (*str1 != *str2)
			return (*(unsigned char *) str1 - *(unsigned char *) str2);
		str1++;
		str2++;
		n--;
	}
	if (n > 0 && *str1 != *str2)
		return (*(unsigned char *) str1 - *(unsigned char *) str2);
	return (0);
}
