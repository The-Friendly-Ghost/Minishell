/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:26:15 by pniezen       #+#    #+#                 */
/*   Updated: 2021/10/25 14:27:57 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*is_negativ(int n, int nr, size_t count)
{
	char	*str;

	n *= -1;
	nr = n;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	count = count + 1;
	str = malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '-';
	str[count] = '\0';
	count--;
	while (count != 0)
	{
		str[count] = (nr % 10) + '0';
		nr /= 10;
		count--;
	}
	return (str);
}

static char	*is_positive(int n, int nr, size_t count)
{
	char	*str;

	nr = n;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	str = malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[count] = '\0';
	count--;
	while (nr > 0)
	{
		str[count] = (nr % 10) + '0';
		nr /= 10;
		if (count != 0)
			count--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		nr;
	size_t	count;

	nr = n;
	count = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		return (is_negativ(n, nr, count));
	return (is_positive(n, nr, count));
}
