/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env_data.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 12:56:50 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/21 12:13:12 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * @param *token A pointer to a char * (the token)
 * @return Nothing
 * @note -
 */
void	add_node_to_env_list(t_env *new_node, t_env **env_list)
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

/**
 * @brief Creates a struct for a single env variable.
 * @param *env_var A pointer to a char *
 * @return *t_env (pointer to the new token node) 
 * @note
 */
static t_env	*create_new_node(char *env_var)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	if (ft_strchr(env_var, '='))
		new_node->var_name = ft_strdup_before_char(env_var, '=');
	else
		new_node->var_name = ft_strdup(env_var);
	new_node->has_value = check_if_env_has_value(env_var);
	new_node->unset = false;
	if (!ft_strcmp(new_node->var_name, "OLDPWD"))
	{
		new_node->value = NULL;
		new_node->has_value = false;
	}
	if (new_node->has_value == true)
		new_node->value = ft_strdup_after_char(env_var, '=');
	else
		new_node->value = NULL;
	new_node->export_unset = false;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

/**
 * @brief 
 * @param **env_list address to the first node
 * @return Nothing
 * @note extern char **environ is a variable that is defined
 * in the readline.h. Therefore, it can be called from anywhere
 * in the program.
 */
static bool	set_environment_variables(t_env **env_list)
{
	extern char		**environ;
	unsigned int	i;
	t_env			*new_node;

	i = 0;
	*env_list = NULL;
	while (environ[i])
	{
		new_node = create_new_node(environ[i]);
		if (new_node == NULL)
			return (false);
		add_node_to_env_list(new_node, env_list);
		i++;
	}
	return (true);
}

/**
 * @brief Returns the address to the list with environment variables
 * @param nothing
 * @return Pointer to the list of environment variables
 * @note -
 */
t_env	**get_env_list(void)
{
	t_program	*program;
	t_env		**env;

	program = get_program();
	env = program->env_list;
	return (env);
}

/**
 * @brief If the program struct already exists, it simply gets
 * returned. If the program isn't created yet, this function calls
 * other functions that create the program struct.
 * @param nothing
 * @return Pointer to the program struct
 * @note -
 */
t_program	*get_program(void)
{
	static t_program	program;

	if (program.env_list)
		return (&program);
	program.env_list = malloc(sizeof(t_env *));
	if (!program.env_list)
		exit(12);
	if (set_environment_variables(program.env_list) == false)
	{
		destroy_env_list(program.env_list);
		exit(12);
	}
	set_shlvl(program.env_list);
	program.exit_code = 0;
	program.amount_commands = 1;
	return (&program);
}
