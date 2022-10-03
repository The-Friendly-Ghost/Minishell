/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 16:56:17 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/03 17:25:03 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Loops over a string as long as there is no single quote found.
 * It then returns if a single quote or null-character is found.
 * @param str The content of the token
 * @return If a single quote is found, the position 1 to the right is returned.
 * If a null-character is found, return the position of the null-character.
 * @note
 */
static unsigned int	skip_single_quotes(char *str, unsigned int i)
{
	while (str[i] != '\'' && str[i])
		i++;
	if (str[i] == '\0')
		return (i);
	else
		return (i + 1);
}

/**
 * @brief Scans for dollar signs inside of the string. If dollar sign is found,
 * @param str The content of the token
 * @return **token_list - Pointer to the first element of the linked list 
 * @note ft_getenv > env_utils.c | id_env_var > expander_utils.c |
 * expand_env_var > expander_utils.c
 */
static char	*search_env_variables(char *str)
{
	int		i;
	char	*env_var_name;
	char	*env_var_value;
	char	*temp;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i = skip_single_quotes(str, i + 1);
		if (str[i] == '\0')
			return (str);
		if ((i >= 1 && str[i - 1] != '\\' && str[i] == '$')
			|| (i == 0 && str[i] == '$'))
		{
			env_var_name = id_env_var(str + i);
			env_var_value = ft_getenv(env_var_name + 1);
			temp = str;
			str = expand_env_var(env_var_name, env_var_value, str, i);
		}
		i++;
	}
	return (free(temp), str);
}

/**
 * @brief Expands environment variable names inside tokens.
 * @param **token_list - Pointer to the first element of the linked list 
 * @return **token_list - Pointer to the first element of the linked list 
 * @note
 */
t_token	**expander(t_token **token_list)
{
	t_token	*temp;

	temp = *token_list;
	while (temp)
	{
		if (temp->type == string || temp->type == enviroment_variable)
			temp->content = search_env_variables(temp->content);
		temp = temp->next;
	}
	return (token_list);
}
