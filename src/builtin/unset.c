/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 15:06:33 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/03 16:47:52 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*delete_env_var(t_env *env_temp)
{
	t_env	*next;
	t_env	*prev;

	prev = env_temp->previous;
	next = env_temp->next;
	if (prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->previous = prev;
	if (env_temp->value != NULL)
		free(env_temp->value);
	if (env_temp->var_name != NULL)
		free(env_temp->var_name);
	free(env_temp);
	if (prev == NULL)
		return (next);
	while (prev->previous)
		prev = prev->previous;
	return (prev);
}

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
