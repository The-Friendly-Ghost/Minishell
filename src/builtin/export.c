/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:44:35 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/13 12:03:31 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"

/**
 * @brief Checks if the given name is in the env.
 * If it is in the env, it returns true, else false.
 * @param name The given variable name.
 * @return bool
 */
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

bool	valid_var_name(char *var_name, char *var_name2, char *equal_sign)
{
	char	*var;
	char	*var2;
	char	*joined;
	int		i;

	i = 0;
	while (var_name[i])
	{
		if (!is_quote(var_name[i])
			&& (var_name[i] <= 47 || (var_name[i] >= 58 && var_name[i] < 61)
				|| (var_name[i] > 61 && var_name[i] <= 64)
				|| var_name[i] >= 123))
		{
			var = ft_strtrim(var_name, "\'\"");
			if (var_name2)
			{
				var2 = ft_strjoin("=", var_name2);
				joined = ft_strjoin(var, var2);
			}
			else
			{
				if (ft_strchr(equal_sign, '='))
					joined = ft_strjoin(var, "=");
				else
					joined = var;
			}
			return (err_msg("export: `", joined, "': not a valid idenfitier"),
				set_exit_code(1), false);
		}
		i++;
	}
	return (true);
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
	if (!valid_var_name(token_list->next->content, NULL, "="))
		return ;
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
