/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 16:34:44 by pniezen       #+#    #+#                 */
/*   Updated: 2021/10/20 14:34:39 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	void	*ptr;
	size_t	count;

	count = ft_strlen(s1) + 1;
	ptr = malloc(count * sizeof(char));
	if (!ptr)
		return (NULL);
	return (ft_memcpy(ptr, s1, count));
}
