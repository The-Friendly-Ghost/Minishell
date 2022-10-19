/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 13:20:25 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/19 14:48:51 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static void	check_set_infile(char *token)
{
	if (access(token, F_OK | R_OK | W_OK) == -1)
		return ((void)printf(
				"minishell: %s: %s\n",
				token, strerror(errno)), set_exit_code(errno));
}

int	check_redirect(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (temp && temp->type != is_pipe)
	{
		if (temp->type == infile)
			check_set_infile(temp->content);
		else if (temp->type == redirect_output)
			return (1);
		else if (temp->type == redirect_output_append)
			return (1);
		temp = temp->next;
	}
	return (1);
}

char	**itterate_redirect(t_token *token_list, char *cmd)
{
	t_token	*temp;
	char	*tmp;
	char	*file;
	char	**new_argv;

	temp = token_list;
	file = NULL;
	if (temp->type == redirect_input)
		return (NULL);
	temp = temp->next;
	while (temp)
	{
		if (file)
			free(file);
		if (temp->next && temp->type == redirect_input)
		{
			if (access(temp->next->content, F_OK | R_OK | W_OK) == -1)
				return ((void)printf(
						"minishell: %s: No such file or directory\n",
						temp->next->content), set_exit_code(1), NULL);
			temp = temp->next;
			continue ;
		}
		tmp = ft_strdup(temp->content);
		file = ft_strjoin(" ", tmp);
		free(tmp);
		temp = temp->next;
	}
	tmp = file;
	file = ft_strjoin(ft_strdup(cmd), tmp);
	new_argv = ft_split(file, ' ');
	return (free(file), free(tmp), new_argv);
}
