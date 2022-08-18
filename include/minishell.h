/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:11:43 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/18 14:09:31 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>

typedef struct s_token {
	unsigned int	id;
	unsigned int	type;
	char			*content;
	t_token			*next;
	t_token			*previous;
}	t_token;

typedef enum e_token_type {
	string_single_quote = 1,
	string_double_quote,
	string_without_quote,
	redirect_input,
	redirect_output,
	delimiter,
	redirect_output_append,
	pipe,
	enviroment_variable,
	print_exit_code,
	echo,
	cd,
	pwd,
	export,
	unset,
	env,
	exit_program
}	t_token_type;

//parser.c

t_token			**parser(char **token_array);

//determine_token_type.c

unsigned int	determine_token_type(char *token);

//destroy_parser.c

void			destroy_token_array(char **token_array);
void			destroy_token_list(t_token **token_list);

//parser_utils.c

int				ft_strcmp(const char *s1, const char *s2);

#endif
