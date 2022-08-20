/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/20 12:31:03 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/20 15:31:38 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"

int	len_wrds(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_is_whitespace(str[i]))
			count++;
		while (!ft_is_whitespace(str[i]) && str[i])
			i++;
		while (ft_is_whitespace(str[i]) && str[i])
			i++;
	}
	return (count);
}

char	*copy_on_dilim(const char *str, char *dst, int *i, char dilim)
{
	dst[*i] = dilim;
	*i += 1;
	while (str[*i] != dilim)
	{
		dst[*i] = str[*i];
		*i += 1;
	}
	dst[*i] = dilim;
	dst[*i + 1] = '\0';
	return (dst);
}

char	*get_word(char **words, const char *str, int n, int total_words)
{
	char	*dst;
	char	dilim;
	int		i;

	i = 0;
	dst = malloc((total_words + 1) * sizeof(char));
	dilim = is_quote(str[i]);
	if (dilim)
	{
		words[n] = copy_on_dilim(str, dst, &i, dilim);
		return (*words);
	}
	while (!ft_is_whitespace(str[i]) && str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	words[n] = dst;
	return (*words);
}

void	make_free(char **words, int n)
{
	while (n > 0)
		free(words[n]);
	n--;
}

void	skip_word_and_whitespace(char *str, int *i)
{
	while (!ft_is_whitespace(str[*i]) && str[*i])
		*i += 1;
	while (ft_is_whitespace(str[*i]) && str[*i])
		*i += 1;
}
