/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 15:19:53 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/18 11:18:15 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Compares two strings that are given as parameters. 
 * @param s1 First string
 * @param s2 Second string
 * @return 0 if strings are the same. Any other number if strings are
 * not the same.
 * @note
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned long long	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
