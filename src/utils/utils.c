/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:35:19 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/25 11:42:11 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenlen(t_token *token_list)
{
	t_token	*temp;
	int		count;

	temp = token_list;
	count = 0;
	while (temp)
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
