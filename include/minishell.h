/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:11:43 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/20 22:18:35 by cpost         ########   odam.nl         */
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
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token {
	unsigned int	id;
	unsigned int	type;
	char			*content;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_env {
	char			*var_name;
	char			*value;
	struct s_env	*next;
	struct s_env	*previous;
}	t_env;

typedef struct s_program {
	int		exit_code;
	t_env	**env_list;
}	t_program;

typedef enum e_token_type {
	string_single_quote = 1,
	string_double_quote,
	string_without_quote,
	redirect_input,
	redirect_output,
	delimiter,
	redirect_output_append,
	is_pipe,
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

//env_utils.c

char			*ft_strdup_before_char(const char *str, char c);
char			*ft_strdup_after_char(const char *str, char c);

#endif
