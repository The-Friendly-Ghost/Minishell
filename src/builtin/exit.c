/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 14:42:20 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/30 10:02:54 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static void	print_fork_exit(void)
{
	if (get_program()->amount_commands == 1)
		ft_putendl_fd("exit", 2);
}

static char	*remove_whitespace(char *str, int i, unsigned long long num,
		char c)
{
	char				*ret;

	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		c = str[i];
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (str[i] - '0') + (num * 10);
		if ((c == '+' && num > LLONG_MAX)
			|| (c == '-' && num > (unsigned long long)LLONG_MAX + 1))
			return (NULL);
		i++;
	}
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] || num == 0)
		return (NULL);
	ret = ft_strtrim(str, " ");
	return (ret);
}

static void	clean_exit(void)
{
	destroy_env_list(get_program()->env_list);
}

/**
 * @brief 
 * @param token_list the linked list with the tokens in it
 * @return 
 * @note
 */
void	exit_minishell(t_token *token)
{
	char	*removed_quotes;
	char	*trimmed_str;

	if (token->next == NULL || token->next->type == is_pipe)
		return (print_fork_exit(), destroy_token_list(&token),
			clean_exit(), exit(0));
	removed_quotes = token->next->content;
	if (token->next->content[0] == '\'')
		removed_quotes = ft_strtrim(token->next->content, "\'");
	else if (token->next->content[0] == '\"')
		removed_quotes = ft_strtrim(token->next->content, "\"");
	if (!removed_quotes)
		return (err_msg(NULL, NULL, NULL));
	trimmed_str = remove_whitespace(removed_quotes, 0, 0, '+');
	if (token->next && token->next->content && !trimmed_str)
		return (print_fork_exit(), err_msg("exit: ", removed_quotes,
				": numeric argument required"), destroy_token_list(&token),
			clean_exit(), free(trimmed_str), exit(255));
	if (token->next && token->next->content && token->next->next
		&& token->next->next->content && token->next->next->type != is_pipe)
		return (print_fork_exit(), free(trimmed_str),
			err_msg("exit: ", "too many arguments", NULL), set_exit_code(1));
	if (token->next && token->next->content && str_is_num(trimmed_str))
		return (print_fork_exit(), destroy_token_list(&token),
			clean_exit(), exit(ft_atoi(trimmed_str)));
}
