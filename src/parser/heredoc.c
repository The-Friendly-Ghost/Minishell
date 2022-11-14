/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 09:44:34 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/14 11:23:44 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

/**
 * @brief Changes the content and the token type of a token.
 * @param token A pointer to a token.
 * @param new_content The new content that has to be set to token->content
 * @param new_type The new token type that the token has to be set to
 * @return Nothing
 */
static void	edit_token(t_token *token, char *new_content,
		t_token_type new_type)
{
	if (token->content)
		free(token->content);
	token->content = new_content;
	token->type = new_type;
}

/**
 * @brief Changes the content and the token type of a token.
 * @param token A pointer to a token.
 * @param new_content The new content that has to be set to token->content
 * @param new_type The new token type that the token has to be set to
 * @return Nothing
 */
static char	*trim_quote(char *content)
{
	int		i;
	int		len;
	char	*trimmed_str;

	i = 0;
	len = 0;
	while (content[i] != '\0')
	{
		if (content[i] != '"' && content[i] != '\'')
			len++;
		i++;
	}
	trimmed_str = ft_calloc((len + 1), sizeof(char));
	i = 0;
	len = 0;
	while (content[i] != '\0')
	{
		if (content[i] != '"' && content[i] != '\'')
		{
			trimmed_str[len] = content[i];
			len++;
		}
		i++;
	}
	return (trimmed_str);
}

static bool	wait_hd(t_token *token)
{
	int	child_state;

	signal(SIGINT, kill_heredoc);
	waitpid(get_program()->hd_pid, &child_state, 0);
	if (child_state)
		return (false);
	edit_token(token, ft_strdup(token->heredoc_file), infile);
	edit_token(token->previous, ft_strdup("<"), redirect_input);
	return (true);
}

/**
 * @brief First, a filename is created by joining 'Heredoc_temp' and
 * the token_id togheter. This garantuees a unique filename. We then
 * open this filename and start writing to it is inputted on the
 * command line. If input == delimiter, we break out of the loop.
 * But before we do that we swap some content in the tokens and close
 * the fd of the file.
 * @param token A pointer to the token with a delimiter in it.
 * @return Nothing
 * @note A newline has to be written after every write call, because readline
 * does not read a newline when 'enter' is pressed.
 */
static bool	get_heredoc_input(t_token *token, char *token_id)
{
	char		*input;
	char		*p_input;
	int			fd;

	token->heredoc_file = ft_strjoin("/tmp/Heredoc_temp", token_id);
	if (!token->heredoc_file)
		return (false);
	free(token_id);
	get_program()->hd_pid = fork();
	if (get_program()->hd_pid == -1)
		return (false);
	else if (get_program()->hd_pid == 0)
	{
		fd = open(token->heredoc_file, O_TRUNC | O_WRONLY | O_CREAT, 0777);
		while (1)
		{
			input = readline("> ");
			p_input = search_env_variables(input, 0, false);
			if (!p_input || !ft_strcmp(p_input, trim_quote(token->content)))
				return (close(fd), exit(0), false);
			ft_putendl_fd(p_input, fd);
			free(p_input);
		}
	}
	return (wait_hd(token));
}

/**
 * @brief Checks if there are any delimiters inside of the token list. If a
 * token is found which is a delimiter, this token is then sent to
 * 'get_heredoc_input' along with the token id of the token.
 * @param token_list A pointer to the first token of the token list
 * @return Nothing
 */
bool	expand_heredocs(t_token *token_list)
{
	t_token		*token;

	token = token_list;
	while (token)
	{
		if (token->previous && token->previous->type == delimiter)
			if (!get_heredoc_input(token, ft_itoa(token->id)))
				return (false);
		token = token->next;
	}
	init_signal_handler();
	return (true);
}
