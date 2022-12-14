/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 14:44:45 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/26 18:36:24 by pniezen       ########   odam.nl         */
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
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# define READ_END 0
# define WRITE_END 1

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
	pid_t	hd_pid;
	int		std_backup[2];
	int		amount_commands;
	t_env	**env_list;
}	t_program;

typedef struct s_redirect {
	int		fd_out;
	int		fd_in;
	int		id_last_in;
	int		redirects_count;
	int		arg_count;
	char	**arg_arr;
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
					int i);

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

//parser/set_pipe_amount.c

bool			set_amount_of_commands(t_token **token_list);

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

void			new_env_var(t_env **env_list, char *new_var, char *new_value);
bool			change_env_var(char *var_name, char *new_value, bool export);
void			set_shlvl(t_env **env_list);
t_env			*delete_env_var(t_env *env_temp);
void			new_env_var(t_env **env_list, char *new_var, char *new_value);

//builtin/

void			echo_builtin(t_token *token_list, int nl);
void			print_env(void);
void			print_pwd(void);
void			print_export_env(void);
void			sort_env_list(t_env **begin_list);
void			export_env_var(t_token *token_list);
void			unset_env_var(t_token *token_list);
void			cd_builtin(t_token *token_list);
void			exit_minishell(t_token *token_list);

//test_functions

void			print_token_list(t_token *token_list);
void			print_2d_array(char **array);

//executor/

void			exec_command(t_token **token_list);
bool			check_redirect(t_token *token_list, t_redirect *rd);
char			**itterate_redirect(t_token *token_list, char *cmd);
void			set_heredoc(t_token *token_list, t_redirect *rd);
bool			expand_heredocs(t_token *token_list);
bool			backup_std_and_set_signals(void);
void			restore_std(void);
t_token			*destroy_command(t_token *token_list);
void			set_dup(t_redirect *rd);
void			set_pipes(int *ends, t_token *token);
bool			is_last_command(t_token *token_list);
pid_t			ft_get_a_pid(void);
void			wait_processes(pid_t pid, bool child);
char			*create_executable_path(t_token *token_list);
t_token			*delete_redirects_from_list(t_token *token_list);
bool			cmd_is_builtin(t_token *token_list);

//utils/

int				ft_tokenlen(t_token *token_list);
char			**ft_nulloc(int n_point);
void			err_msg(char *str1, char *str2, char *str3);
bool			str_is_num(char *num);

//utils/error_messages.c
void			err_msg(char *str1, char *str2, char *str3);

//signal_handlers

void			init_signal_handler(void);
void			executor_signal_handler(int signum);
void			kill_heredoc(int signum);

#endif
