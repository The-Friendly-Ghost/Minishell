/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:44:35 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/10 14:11:21 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_node_to_env_list(t_env *new_node, t_env **env_list)
{
	t_env	*temp;

	if (!(*env_list))
		*env_list = new_node;
	else
	{
		temp = *env_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
		new_node->previous = temp;
	}
}

static t_env	*create_new_node(char *env_var, char *env_value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var_name = ft_strdup(env_var);
	new_node->value = ft_strdup(env_value);
	if (ft_strlen(env_value) == 0)
		new_node->unset = true;
	else
	{
		new_node->has_value = true;
		new_node->unset = false;
	}
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

static void	print_export_env(void)
{
	t_env		**env;
	t_env		*temp;

	env = get_env_list();
	if (!(*env))
		return (set_exit_code(127));
	temp = *env;
	while (temp)
	{
		if (!temp->has_value)
			printf("declare -x %s\n", temp->var_name);
		else
			printf("declare -x %s=\"%s\"\n", temp->var_name, temp->value);
		temp = temp->next;
	}
	set_exit_code(0);
}

void	export_env_var(t_token *token_list)
{
	t_env	*env;
	t_env	*new_node;
	char	**split;
	char	*temp;
	int		i;

	i = ft_tokenlen(token_list);
	if (i == 1)
		return (print_export_env());
	if (ft_strrchr(token_list->next->content, '='))
	{
		if (token_list->next->content[0] == '=')
		{
			set_exit_code(1);
			return ((void)printf("\
minishell: export: `%s': not a valid identifier\n", token_list->next->content));
		}
		split = ft_split(token_list->next->content, '=');
		if (!split)
			return ;
	}
	// ^^^ DONE ^^^ //
	env = *get_env_list();
	while (env)
	{
		if (!ft_strcmp(env->var_name, split[0]))
		{
			if (split[1])
			{
				env->value = ft_strdup(split[1]);
				env->has_value = true;
				return (destroy_double_array(split));
			}
			else
			{
				temp = env->value;
				env->value = "";
				env->has_value = false;
				return (free(temp), destroy_double_array(split));
			}
		}
		if (env->has_value
			&& !ft_strcmp(env->var_name, token_list->next->content))
			return ;
		env = env->next;
	}
	// ^^^ DONE //
	if (token_list->next->content[ft_strlen(token_list->next->content) - 1] == '=')
	{
		new_node = create_new_node(split[0], "");
		if (!new_node)
			return ;
		add_node_to_env_list(new_node, get_env_list());
		set_exit_code(0);
		return (destroy_double_array(split));
	}
	new_node = create_new_node(token_list->next->content, "");
	if (!new_node)
		return ;
	add_node_to_env_list(new_node, get_env_list());
	destroy_double_array(split);
	set_exit_code(0);
}
