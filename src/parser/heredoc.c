/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 09:44:34 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/28 15:38:36 by cpost         ########   odam.nl         */
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
static void	get_heredoc_input(t_token *token, char *token_id)
{
	const char	prompt[] = "> ";
	char		*input;
	int			fd;

	token->heredoc_file = ft_strjoin("/tmp/Heredoc_temp", token_id);
	free(token_id);
	fd = open(token->heredoc_file, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	while (1)
	{
		input = readline(prompt);
		if (!input || !ft_strcmp(input, trim_quote(token->content)))
		{
			edit_token(token, ft_strdup(token->heredoc_file), infile);
			edit_token(token->previous, ft_strdup("<"), redirect_input);
			close(fd);
			return ;
		}
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
}

/**
 * @brief Checks if there are any delimiters inside of the token list. If a
 * token is found which is a delimiter, this token is then sent to
 * 'get_heredoc_input' along with the token id of the token.
 * @param token_list A pointer to the first token of the token list
 * @return Nothing
 */
void	expand_heredocs(t_token *token_list)
{
	t_token		*token;

	token = token_list;
	while (token)
	{
		if (token->previous && token->previous->type == delimiter)
			get_heredoc_input(token, ft_itoa(token->id));
		token = token->next;
	}
}
