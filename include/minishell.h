/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 14:44:45 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/31 16:05:55 by cpost         ########   odam.nl         */
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
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token {
	int				id;
	int				type;
	char			*content;
	char			*heredoc_file;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_env {
	char			*var_name;
	bool			has_value;
	bool			unset;
	bool			export_unset;
	char			*value;
	struct s_env	*next;
	struct s_env	*previous;
}	t_env;

typedef struct s_program {
	int		exit_code;
	t_env	**env_list;
}	t_program;

typedef struct s_redirect {
	int		fd_out;
	int		fd_in;
	int		id_last_in;
	int		redirects_count;
	int		arg_count;
	char	**arg_str;
}	t_redirect;

typedef enum e_token_type {
	invalid_input,
	string,
	redirect_input,
	redirect_output,
	delimiter,
	infile,
	outfile,
	redirect_output_append,
	is_heredoc,
	is_pipe,
	enviroment_variable,
	print_exit_code,
	echo,
	cd,
	pwd,
	export_var,
	unset,
	env,
	exit_program,
}	t_token_type;

typedef enum e_print_code {
	no_error,
	newline_error,
	redirect_error_input,
	redirect_error_output,
	delimiter_error,
	redirect_append_error,
	pipe_error,
}	t_print_code;

// executor/get_env_array.c

char			**get_env_array(void);

// expander/expander.c

void			expander(t_token *token_list);
char			*search_env_variables(char *str, int i, bool is_double_quote);

// expander/expander_utils.c

char			*id_env_var(char *str);
char			*expand_env_var(char *name, char *value, char *str,
					unsigned int i);

// lexer/

char			**lexer(char *input);
char			**tokenizer(char *input, int token_count);

//parser/

bool			parser(char **token_array, t_token **token_list);

//parser/parser_utils.c

int				ft_strcmp(const char *s1, const char *s2);

//parser/determine_token_type.c

int				determine_token_type(char *token);

//parser/destroy_parser.c

void			destroy_double_array(char **token_array);
void			destroy_token_list(t_token **token_list);
void			destroy_env_list(t_env **env_list);

// parser/parser_syntax_error.c

bool			check_for_syntax_error(t_token *token_list);

//environment/get_env_data.c

t_program		*get_program(void);
void			add_node_to_env_list(t_env *new_node, t_env **env_list);
t_env			**get_env_list(void);

//environment/env_utils.c

void			set_exit_code(int exit_code);
char			*ft_strdup_before_char(const char *str, char c);
char			*ft_strdup_after_char(const char *str, char c);
char			*ft_getenv(const char *name);
bool			check_if_env_has_value(const char *str);

//environment/change_env_var.c

bool			change_env_var(char *var_name, char *new_value, bool export);

//builtin/

void			echo_builtin(t_token *token_list);
void			print_env(void);
void			print_pwd(void);
void			print_export_env(void);
void			export_env_var(t_token *token_list);
void			unset_env_var(char **argv);
void			cd_builtin(t_token *token_list);
void			exit_minishell(t_token *token_list);

//test_functions

void			print_token_list(t_token *token_list);
void			print_2d_array(char **array);

//executor/

char			*get_executable_path(char *command_str);
void			exec_command(t_token *token_list, t_token_type type,
					char **argv);
void			check_redirect(t_token *token_list, t_redirect *rd);
char			**itterate_redirect(t_token *token_list, char *cmd);
void			set_heredoc(t_token *token_list, t_redirect *rd);
void			expand_heredocs(t_token *token_list);

//utils/

int				ft_tokenlen(t_token *token_list);
char			**ft_nulloc(int n_point);
void			err_msg(char *str1, char *str2, char *str3);
bool			str_is_num(char *num);

//signal_handlers

void			init_signal_handler(void);
void			executor_signal_handler(int signum);

#endif
