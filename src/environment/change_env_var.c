/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_env_var.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 15:15:31 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/12 11:17:35 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_values(t_env *temp, char *new_value, bool export)
{
	if (export)
	{
		temp->export_unset = true;
		if (new_value == NULL)
			temp->has_value = false;
		else
			temp->has_value = true;
	}
	else
	{
		if (new_value == NULL)
			temp->has_value = false;
		else
			temp->has_value = true;
	}
}

/**
 * @brief Changes the value of an environment variable. 
 * @param var_name The name of the environment variable that has to be changed
 * @param new_value The new value that 'var_name' has to be changed to
 * @return True if 'var_name' was succesfully changed to the new value. False
 * if 'var_name' was not found.
 * @note Note that 'new_value' and 'var_name' do not get freed in case 'var_name'
 * was not found. This is because sometimes it might be neccessary
 * to retain a certain pointer. If pointers have to be freed, it has to be done
 * in another function.
 */
bool	change_env_var(char *var_name, char *new_value, bool export)
{
	t_env	**env_list;
	t_env	*temp;

	env_list = get_env_list();
	temp = *env_list;
	while (temp)
	{
		if (!ft_strcmp(temp->var_name, var_name))
		{
			if (temp->value)
				free(temp->value);
			temp->value = new_value;
			set_values(temp, new_value, export);
			return (true);
		}
		temp = temp->next;
	}
	return (false);
}

/**
 * @brief Deletes a environment variable from the environment list.
 * @param env_temp Pointer to the node (env var) that has to be deleted
 * @return Pointer to the first node of the env_list.
 * @note 
 * 1. This function returns a pointer to the first node of the env_list.
 * This means that in the calling function, the function has to be called as
 * follows : "*env_list = delete_env_var(env_temp);" . Where env_list is
 * a double pointer (**env_list).
 * 2. If a NULL is passed as parameter, this function segfaults. So only a
 * valid node can be passed as parameter.
 */
t_env	*delete_env_var(t_env *env_temp)
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

/**
 * @brief Adds a new env_var to the env_var list
 * @param env_list
 * @return 
 */
void	new_env_var(t_env **env_list, char *new_var, char *new_value)
{
	t_env	*temp;
	t_env	*new_node;

	temp = *env_list;
	while (temp->next)
		temp = temp->next;
	new_node = malloc(sizeof(t_env));
	temp->next = new_node;
	new_node->previous = temp;
	new_node->next = NULL;
	new_node->var_name = new_var;
	new_node->value = new_value;
	new_node->unset = false;
	new_node->export_unset = false;
	if (new_value)
		new_node->has_value = true;
	else
		new_node->has_value = false;
}

/**
 * @brief Sets the correct SHLVL in the env vars. Basically, if SHLVL exists,
 * SHLVL gets incremented by 1. If SHLVL doesn't exist, a new SHLVL will be
 * set to 1.
 * @param env_list
 * @return 
 */
void	set_shlvl(t_env **env_list)
{
	t_env	*temp;
	int		num;

	temp = *env_list;
	while (temp)
	{
		if (ft_strcmp(temp->var_name, "SHLVL") == 0)
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
		new_env_var(env_list, ft_strdup("SHLVL"), ft_strdup("1"));
	else
	{
		if (temp->has_value && str_is_num(temp->value))
		{
			num = ft_atoi(temp->value);
			free(temp->value);
			num += 1;
			temp->value = ft_itoa(num);
		}
	}
}
