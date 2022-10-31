/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 16:56:17 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/31 10:36:20 by pniezen       ########   odam.nl         */
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

static void	set_double_quote(bool *is_double_quote)
{
	if (*is_double_quote == true)
		*is_double_quote = false;
	else
		*is_double_quote = true;
}

/**
 * @brief Scans for dollar signs inside of the string. If dollar sign is found,
 * @param str The content of the token
 * @return **token_list - Pointer to the first element of the linked list 
 * @note ft_getenv > env_utils.c | id_env_var > expander_utils.c |
 * expand_env_var > expander_utils.c
 */
char	*search_env_variables(char *str, int i, bool is_double_quote)
{
	char	*env_var_name;
	char	*env_var_value;
	char	*temp_str;

	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\"')
			set_double_quote(&is_double_quote);
		if (str[i] == '\'' && is_double_quote == false)
			i = skip_single_quotes(str, i + 1);
		if (str[i] == '\0')
			return (str);
		if (str[i] == '$')
		{
			env_var_name = id_env_var(str + i);
			env_var_value = ft_getenv(env_var_name + 1);
			if (!env_var_value && env_var_name[1] == '/')
				return (str);
			temp_str = str;
			str = expand_env_var(env_var_name, env_var_value, str, i);
			free(temp_str);
		}
		i++;
	}
	return (str);
}

/**
 * @brief Expands environment variable names inside tokens.
 * @param **token_list - Pointer to the first element of the linked list 
 * @return **token_list - Pointer to the first element of the linked list 
 * @note
 */
void	expander(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (temp)
	{
		if (temp->type == string || temp->type == enviroment_variable)
			temp->content = search_env_variables(temp->content, 0, false);
		temp = temp->next;
	}
}
