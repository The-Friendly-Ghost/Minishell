/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 15:06:33 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/04 11:22:08 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Searches for variables passed from the command line. If a variable
 * is found, it will be removed from the environment variable list.
 * @param token_list A pointer to the first node of the token list.
 * @return Nothing
 */
void	unset_env_var(t_token *token_list)
{
	t_env	**env_list;
	t_env	*env_temp;
	t_token	*tok_temp;

	env_list = get_env_list();
	tok_temp = token_list->next;
	while (tok_temp && tok_temp->type != is_pipe)
	{
		env_temp = *env_list;
		while (env_temp)
		{
			if (env_temp->var_name && !ft_strcmp(env_temp->var_name,
					tok_temp->content))
			{
				*env_list = delete_env_var(env_temp);
				break ;
			}
			env_temp = env_temp->next;
		}
		tok_temp = tok_temp->next;
	}
}
