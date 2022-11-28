/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:44:35 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/28 11:23:11 by pniezen       ########   odam.nl         */
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

static bool	is_it_alpha(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
		return (false);
	while (ft_isalpha(str[i]))
		i++;
	if (str[i] == '\0')
		return (true);
	else if (str[i] == '=')
		return (true);
	return (false);
}

void	export_env_var(t_token *token_list)
{
	char	**split;
	char	*msg;
	char	*split_1;

	split_1 = NULL;
	if (!is_it_alpha(token_list->next->content))
	{
		msg = ft_strjoin("`", token_list->next->content);
		set_exit_code(1);
		return (err_msg(msg, "': not a valid identifier", NULL), free(msg));
	}
	split = ft_split(token_list->next->content, '=');
fprintf(stderr, "split = [%s]\n", split[0]);
	if (!split)
		return (set_exit_code(12), err_msg(NULL, NULL, NULL));
	if (split[1] && split[1][0] == '\'')
		split_1 = ft_strtrim(split[1], "\'");
	if (split[1] && split[1][0] == '\"')
		split_1 = ft_strtrim(split[1], "\"");
	else if (split[1])
		split_1 = ft_strdup(split[1]);
	add_change_env_var(split[0], split_1, token_list);
	free(split_1);
	destroy_double_array(split);
}
