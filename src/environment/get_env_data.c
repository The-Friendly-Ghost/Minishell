/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env_data.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 12:56:50 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/20 23:00:16 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * @param *token A pointer to a char * (the token)
 * @return Nothing
 * @note -
 */
static bool	add_node_to_env_list(t_env *new_node, t_env **env_list)
{
	t_env	*temp;

	//printf("new_node = %p\n", new_node);
	//printf("env_list = %p\n", *env_list);
	if (!(*env_list))
	{
		*env_list = new_node;
	}
	else
	{
		temp = *env_list;
		while (temp->next)
			temp = temp->next;
		new_node->previous = temp;
		temp->next = new_node;
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
	new_node->var_name = ft_strdup_before_char(env_var, '=');
	new_node->value = ft_strdup_after_char(env_var, '=');
	new_node->next = NULL;
	new_node->previous = NULL;
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
	else
	{
		program.env_list = malloc(sizeof(program.env_list));
		if (set_environment_variables(program.env_list) == false)
		{
			// Write error naar STDERROR
			// Set error exit code
			// destroy_program_struct(&program);
			return (NULL);
		}
		program.exit_code = 0;
		return (&program);
	}
}
