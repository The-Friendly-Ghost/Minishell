/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:44:35 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/11 15:46:34 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_getenv_bool(const char *name)
{
	t_env		**env;
	t_env		*temp;

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
	if (env_value == NULL)
		new_node->value = NULL;
	else
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
		{
			if (temp->value == NULL)
				printf("declare -x %s=\"\"\n", temp->var_name);
			else
				printf("declare -x %s=\"%s\"\n", temp->var_name, temp->value);
		}
		temp = temp->next;
	}
	set_exit_code(0);
}

void	export_env_var(t_token *token_list)
{
	t_env	*new_node;
	char	**split;

	set_exit_code(0);
	if (ft_tokenlen(token_list) == 1)
		return (print_export_env());
	if (token_list->next->content[0] == '=')
		return (set_exit_code(1), (void)printf("\
minishell: export: `%s': not a valid identifier\n", token_list->next->content));
	split = ft_split(token_list->next->content, '=');
	if (!split)
		return (set_exit_code(12));
	if (ft_getenv_bool(split[0]) && !ft_strchr(token_list->next->content, '='))
		return (destroy_double_array(split));
	printf("1\n");
	if (ft_getenv_bool(split[0]) && split[1])
	{
		printf("1.5\n");
		return ((void)change_env_var(split[0], ft_strdup(split[1]), true), destroy_double_array(split));
	}
	printf("2\n");
	if (ft_getenv_bool(split[0]))
		return ((void)change_env_var(split[0], NULL, true), destroy_double_array(split));
	printf("3\n");
	if (split[1])
		new_node = create_new_node(split[0], split[1]);
	else
		new_node = create_new_node(split[0], NULL);
	printf("4\n");
	if (!new_node)
		return (set_exit_code(12));
	if (ft_strchr(token_list->next->content, '='))
		new_node->has_value = true;
	else
		new_node->has_value = false;
	add_node_to_env_list(new_node, get_env_list());
	return (destroy_double_array(split));
}
