/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:35:19 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/28 10:51:18 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenlen(t_token *token_list)
{
	t_token	*temp;
	int		count;

	temp = token_list;
	count = 0;
	while (temp && temp->type != is_pipe)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

/**
 * @brief Creates a new array filled with NULL pointers.
 * @param n_point The amount of NULL pointers to create.
 * @return Pointer to the newly created array of NULL pointers
 * @note
 */
char	**ft_nulloc(int n_point)
{
	char	**ptr;
	int		i;

	ptr = malloc(n_point * sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < n_point)
		ptr[i++] = NULL;
	return (ptr);
}

bool	str_is_num(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i])
	{
		if (!ft_isquote(num[i]) && !ft_isdigit(num[i]))
			return (false);
		i++;
	}
	return (true);
}

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
