/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:35:19 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/26 14:47:23 by pniezen       ########   odam.nl         */
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

// void	err_msg(char *cmd, char *arg, char *content)
	// printf("%s %s %s\n", cmd, arg, content);
void	err_msg(char *str1, char *str2, char *str3)
{
	char	*err_promt;
	char	*err_msg;
	char	*temp;

	if (str1 && str2 && str3)
	{
		temp = ft_strjoin("minishell: ", str1);
		err_promt = ft_strjoin(temp, str2);
		err_msg = ft_strjoin(err_promt, str3);
		free(err_promt);
	}
	else if (str1 && str2)
	{
		temp = ft_strjoin("minishell: ", str1);
		err_msg = ft_strjoin(temp, str2);
	}
	else
		err_msg = ft_strjoin("minishell: ", str1);
	if (!err_msg)
	{
		ft_putendl_fd("Fatal error", 2);
		exit(ENOMEM);
	}
	ft_putendl_fd(err_msg, 2);
	return (free(temp), free(err_msg));
}
