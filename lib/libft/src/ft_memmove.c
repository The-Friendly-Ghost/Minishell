/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 16:34:32 by pniezen       #+#    #+#                 */
/*   Updated: 2021/10/27 17:34:44 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;

	i = 0;
	if (!dst && !src)
		return (0);
	if (dst < src)
	{
		while (i < len)
		{
			((char *) dst)[i] = ((const char *) src)[i];
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			((char *) dst)[len - 1] = ((const char *) src)[len - 1];
			len--;
		}
	}
	return (dst);
}
