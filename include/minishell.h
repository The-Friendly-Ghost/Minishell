/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:11:43 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/19 14:35:16 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_token {
	unsigned int	id;
	unsigned int	type;
	char			*content;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_env {
	char			*name;
	bool			is_number;
	long			number_value;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_program {
	int		exit_code;
	t_env	**env;
}	t_program;

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

//get_env_data.c

t_program		*get_program(void);

#endif
