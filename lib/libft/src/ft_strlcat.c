/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 16:34:48 by pniezen       #+#    #+#                 */
/*   Updated: 2021/10/27 17:29:34 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	k = 0;
	if (i >= dstsize)
		return (j + dstsize);
	while (src[k] && (dstsize - i) - 1 > 0)
	{
		dst[i + k] = src[k];
		k++;
		dstsize--;
	}
	dst[i + k] = '\0';
	return (i + j);
}
