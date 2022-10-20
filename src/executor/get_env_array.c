/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 15:14:05 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/20 14:10:33 by cpost         ########   odam.nl         */
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

	len = ft_strlen(env_var->var_name) + ft_strlen(env_var->value) + 2;
	str = malloc(len * sizeof(char));
//PROTECTEN
	i = 0;
	x = 0;
	while (env_var->var_name != NULL && env_var->var_name[i])
		str[x++] = env_var->var_name[i++];
	str[x++] = '=';
	i = 0;
	while (env_var->value != NULL && env_var->value[i])
		str[x++] = env_var->value[i++];
	str[x] = '\0';
	return (str);
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
	char	**env_list;
	int		node;

	node = 0;
	env = get_env_list();
	if (!(*env))
		return (NULL);
	temp = *env;
	while (temp)
	{
		node++;
		temp = temp->next;
	}
	env_list = malloc(sizeof(char *) * (node + 1));
//PROTECTEN
	temp = *env;
	node = 0;
	while (temp)
	{
		env_list[node++] = create_env_string(temp);
		temp = temp->next;
	}
	env_list[node] = NULL;
	return (env_list);
}
