/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:44:35 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/02 15:24:42 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_getenv_bool(const char *name)
{
	t_env	**env;
	t_env	*temp;

	if (name == NULL)
		return (false);
	env = get_env_list();
	if (!(*env))
		return (false);
	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->var_name, name) == 0)
			return (true);
		temp = temp->next;
	}
	return (false);
}

void	print_export_env(void)
{
	t_env	**env;
	t_env	*temp;

	env = get_env_list();
	if (!(*env))
		return (set_exit_code(127));
	temp = *env;
	while (temp)
	{
		if (!temp->has_value && !temp->export_unset)
		{
			if (!ft_strcmp(temp->var_name, "PATH")
				|| !ft_strcmp(temp->var_name, "HOME"))
			{
				temp = temp->next;
				continue ;
			}
			printf("declare -x %s\n", temp->var_name);
		}
		else
		{
			if (!temp->value && temp->export_unset)
				printf("declare -x %s=\"\"\n", temp->var_name);
			else
				printf("declare -x %s=\"%s\"\n", temp->var_name, temp->value);
		}
		temp = temp->next;
	}
}

void	export_env_var(t_token *token_list)
{
	t_env	**env_list;
	char	**split;
	char	*msg;

	env_list = get_env_list();
	if (token_list->next->content[0] == '=')
	{
		msg = ft_strjoin("`", token_list->next->content);
		set_exit_code(1);
		return (err_msg(msg, "': not a valid indentifier", NULL));
	}
	split = ft_split(token_list->next->content, '=');
	if (!split)
		return (set_exit_code(12));
	if (ft_getenv_bool(split[0]) && !ft_strchr(token_list->next->content, '='))
		return (destroy_double_array(split));
	if (ft_getenv_bool(split[0]))
	{
		if (split[1])
			return ((void)change_env_var(split[0], ft_strdup(split[1]), true),
				destroy_double_array(split));
		return ((void)change_env_var(split[0], NULL, true),
			destroy_double_array(split));
	}
	if (split[1])
		return (new_env_var(
				env_list, ft_strdup(split[0]), ft_strdup(split[1])));
	new_env_var(env_list, ft_strdup(split[0]), NULL);
}
