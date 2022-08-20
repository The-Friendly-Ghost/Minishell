/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_whitespace.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/20 14:15:58 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/20 14:16:51 by pniezen       ########   odam.nl         */
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
