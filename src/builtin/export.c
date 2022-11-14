/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:44:35 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/14 09:25:11 by pniezen       ########   odam.nl         */
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

static bool	prepare_errmsg(char *var_name, char *var_name2)
{
	char	*var;
	char	*var2;
	char	*joined;

	if (var_name[0] == '\'')
		var = ft_strtrim(var_name, "\'");
	if (var_name[0] == '\"')
		var = ft_strtrim(var_name, "\"");
	if (var_name2)
	{
		var2 = ft_strjoin("=", var_name2);
		joined = ft_strjoin(var, var2);
		free(var2);
	}
	else
	{
		if (ft_strchr(var_name, '='))
			joined = ft_strjoin(var, "=");
		else
			joined = var;
	}
	free(var);
	return (err_msg("export: `", joined, "': not a valid idenfitier"),
		set_exit_code(1), free(joined), false);
}

static bool	valid_var_name(char *var_name, char *var_name2)
{
	int		i;

	i = 0;
	while (var_name[i])
	{
		if (!is_quote(var_name[i])
			&& (var_name[i] <= 47 || (var_name[i] >= 58 && var_name[i] < 61)
				|| (var_name[i] > 61 && var_name[i] <= 64)
				|| var_name[i] >= 123))
			if (!prepare_errmsg(var_name, var_name2))
				return (false);
		i++;
	}
	return (true);
}

static void	add_change_env_var(char *spl_0, char *spl_1, t_token *token_list)
{
	t_env	**env_list;

	env_list = get_env_list();
	if (ft_getenv_bool(spl_0) && !ft_strchr(token_list->next->content, '='))
		return ;
	if (ft_getenv_bool(spl_0))
	{
		if (spl_1)
			return ((void)change_env_var(spl_0, ft_strdup(spl_1), true));
		return ((void)change_env_var(spl_0, NULL, true));
	}
	if (spl_1)
		return (new_env_var(
				env_list, ft_strdup(spl_0), ft_strdup(spl_1)));
	if (ft_strchr(token_list->next->content, '='))
		return (new_env_var(env_list, ft_strdup(spl_0), ft_strdup("")));
	new_env_var(env_list, ft_strdup(spl_0), NULL);
}

void	export_env_var(t_token *token_list)
{
	char	**split;
	char	*msg;
	char	*split_1;

	if (token_list->next->content[0] == '=')
	{
		msg = ft_strjoin("`", token_list->next->content);
		set_exit_code(1);
		return (err_msg(msg, "': not a valid indentifier", NULL));
	}
	split = ft_split(token_list->next->content, '=');
	if (!split)
		return (set_exit_code(12), err_msg(NULL, NULL, NULL));
	if (!valid_var_name(token_list->next->content, NULL))
		return ;
	if (split[1] && split[1][0] == '\'')
		split_1 = ft_strtrim(split[1], "\'");
	if (split[1] && split[1][0] == '\"')
		split_1 = ft_strtrim(split[1], "\"");
	if (!split_1)
		return (err_msg(NULL, NULL, NULL));
	if (!split[1])
		split_1 = NULL;
	add_change_env_var(split[0], split_1, token_list);
	destroy_double_array(split);
}
