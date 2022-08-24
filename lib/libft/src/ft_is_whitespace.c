/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_whitespace.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 14:39:05 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/24 14:39:09 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_whitespace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	return (0);
}
