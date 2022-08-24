/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
<<<<<<< HEAD
/*   ft_is_whitespace.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/20 14:15:58 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/20 14:16:51 by pniezen       ########   odam.nl         */
=======
/*   is_whitespace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 14:32:19 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/23 14:32:24 by cpost         ########   odam.nl         */
>>>>>>> Casper
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
