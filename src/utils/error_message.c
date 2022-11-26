/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_message.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 13:47:12 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/26 13:19:30 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

static void	run_while(char *str, char *temp, bool is_quote)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = '\0';
	while (str[i])
	{
		if (str[i] == c && is_quote)
		{
			c = '\0';
			is_quote = false;
		}
		else if ((str[i] == '\"' || str[i] == '\'') && !is_quote)
		{
			c = str[i];
			is_quote = true;
		}
		else
			temp[j++] = str[i];
		i++;
	}
}

static char	*trim_quotes(char *str)
{
	char	*temp;

	if (!str)
		return (NULL);
	if (!has_quotes(str))
		return (str);
	if (!ft_isquote(str[0]))
		return (str);
	if (!ft_isquote(str[ft_strlen(str) - 1]))
		return (str);
	temp = ft_calloc(ft_strlen(str), sizeof(char));
	if (!temp)
		return (str);
	run_while(str, temp, false);
	ft_bzero(str, ft_strlen(str));
	ft_memcpy(str, temp, ft_strlen(temp));
	return (free(temp), str);
}

void	err_msg(char *str1, char *str2, char *str3)
{
	char	*err_promt;
	char	*err_msg;
	char	*temp;

	temp = NULL;
	if (str1 && str2 && str3)
	{
		temp = ft_strjoin("minishell: ", trim_quotes(str1));
		err_promt = ft_strjoin(temp, trim_quotes(str2));
		err_msg = ft_strjoin(err_promt, trim_quotes(str3));
		free(err_promt);
	}
	else if (str1 && str2)
	{
		temp = ft_strjoin("minishell: ", trim_quotes(str1));
		err_msg = ft_strjoin(temp, trim_quotes(str2));
	}
	else
		err_msg = ft_strjoin("minishell: ", trim_quotes(str1));
	if (!err_msg)
	{
		ft_putendl_fd("Fatal error", 2);
		return (free(temp), set_exit_code(ENOMEM), exit(ENOMEM));
	}
	return (ft_putendl_fd(err_msg, 2), free(temp), free(err_msg));
}
