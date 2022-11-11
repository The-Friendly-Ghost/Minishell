/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 14:42:20 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/11 14:05:59 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_fork_exit(pid_t *pid)
{
	if (*pid)
		ft_putendl_fd("exit", 2);
}

static char	*remove_quotes(char *content)
{
	char	*temp;
	int		len;
	int		i;

	len = ft_strlen(content) + 1;
	temp = malloc(len * sizeof(char));
	// TODO Error check
	len = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] != '"' && content[i] != '\'')
		{
			temp[len] = content[i];
			len++;
		}
		i++;
	}
	temp[len] = '\0';
	ft_memcpy(content, temp, ft_strlen(temp) + 1);
	free(temp);
	return (content);
}

/**
 * @brief 
 * @param token_list the linked list with the tokens in it
 * @return 
 * @note
 */
void	exit_minishell(t_token *token_list, pid_t *pid)
{
	t_token	*temp;

	temp = token_list;
	if (temp->next == NULL || temp->next->type == is_pipe)
		exit(127);
	else if (temp->next && temp->next->content && temp->next->next
		&& temp->next->next->content && temp->next->next->type != is_pipe)
	{
		print_fork_exit(pid);
		err_msg("exit: ", "too many arguments", NULL);
		set_exit_code(1);
	}
	else if (temp->next && temp->next->content
		&& !str_is_num(remove_quotes(temp->next->content)))
	{
		print_fork_exit(pid);
		err_msg("exit: ", temp->next->content, ": numeric argument required");
		exit(255);
	}
	else if (temp->next && temp->next->content
		&& str_is_num(remove_quotes(temp->next->content)))
	{
		print_fork_exit(pid);
		exit(ft_atoi(remove_quotes(temp->next->content)));
	}
}
