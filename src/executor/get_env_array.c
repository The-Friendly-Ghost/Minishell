/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 15:14:05 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/13 13:31:59 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Sub function of get_env_array. This function receives a single node
 * (struct) and converts it to a char * (string).
 * @param env_var Pointer to a environment variable node.
 * @return Char * (The converted string)
 * @note -
 */
static char	*create_env_string(t_env *env_var)
{
	int		len;
	char	*str;
	int		i;
	int		x;

	len = ft_strlen(env_var->var_name) + ft_strlen(env_var->value) + 4;
	str = malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	x = 0;
	while (env_var->var_name != NULL && env_var->var_name[i])
		str[x++] = env_var->var_name[i++];
	if (env_var->value)
	{
		str[x++] = '=';
		str[x++] = '\"';
	}
	i = 0;
	while (env_var->value != NULL && env_var->value[i])
		str[x++] = env_var->value[i++];
	if (env_var->value)
		str[x++] = '\"';
	str[x] = '\0';
	return (str);
}

static int	ft_envsize(t_env *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

/**
 * @brief This function converts the linked list with all the environment in
 * it to a 2D-array.
 * @param none
 * @return Pointer to the 2D array
 * @note This function can be passed as the envp paramater in execve.
 */
char	**get_env_array(void)
{
	t_env	**env;
	t_env	*temp;
	char	**env_array;
	int		node;

	node = 0;
	env = get_env_list();
	if (!(*env))
		return (NULL);
	temp = *env;
	env_array = malloc(sizeof(char *) * (ft_envsize(temp) + 1));
	if (!env_array)
		return (NULL);
	temp = *env;
	while (temp)
	{
		// if (temp->unset == false && temp->has_value)
		env_array[node++] = create_env_string(temp);
		if (!env_array[node - 1])
			return (destroy_double_array(env_array), err_msg(NULL, NULL, NULL),
				NULL);
		temp = temp->next;
	}
	env_array[node] = NULL;
	return (env_array);
}
