/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 14:42:20 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/14 17:03:42 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_fork_exit(void)
{
	if (get_program()->amount_commands == 1)
		ft_putendl_fd("exit", 2);
}

static char	*remove_whitespace(char *str)
{
	char	*ret;
	int		i;
	bool	num;

	i = 0;
	num = false;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i++]))
		num = true;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] || !num)
		return (NULL);
	ret = ft_strtrim(str, " ");
	return (ret);
}

/**
 * @brief 
 * @param token_list the linked list with the tokens in it
 * @return 
 * @note
 */
void	exit_minishell(t_token *token_list)
{
	t_token	*temp;
	char	*removed_quotes;
	char	*trimmed_str;

	temp = token_list;
	if (temp->next == NULL || temp->next->type == is_pipe)
		return (print_fork_exit(), exit(0));
	if (temp->next && temp->next->content && temp->next->next
		&& temp->next->next->content && temp->next->next->type != is_pipe)
		return (print_fork_exit(), err_msg("exit: ", "too many arguments",
				NULL), set_exit_code(1));
	removed_quotes = temp->next->content;
	if (temp->next->content[0] == '\'')
		removed_quotes = ft_strtrim(temp->next->content, "\'");
	else if (temp->next->content[0] == '\"')
		removed_quotes = ft_strtrim(temp->next->content, "\"");
	if (!removed_quotes)
		return (err_msg(NULL, NULL, NULL));
	trimmed_str = remove_whitespace(removed_quotes);
	if (temp->next && temp->next->content && !trimmed_str)
		return (print_fork_exit(), err_msg("exit: ", removed_quotes,
				": numeric argument required"),
			exit(255));
	if (temp->next && temp->next->content && str_is_num(trimmed_str))
		return (print_fork_exit(), exit(ft_atoi(trimmed_str)));
}
