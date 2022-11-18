/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 14:16:31 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/15 16:11:22 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	kill_heredoc(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', 1);
	kill(get_program()->hd_pid, SIGTERM);
	set_exit_code(1);
}

void	executor_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("^C", 1);
		set_exit_code(130);
	}
	else if (signum == SIGQUIT)
	{
		rl_replace_line("", 0);
		ft_putendl_fd("^\\Quit: 3", 1);
		set_exit_code(131);
	}
}

static void	handle_crtl_c(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', 1);
	rl_replace_line("\0", 0);
	rl_on_new_line();
	rl_redisplay();
	set_exit_code(1);
}

void	init_signal_handler(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
	signal(SIGINT, handle_crtl_c);
	signal(SIGQUIT, executor_signal_handler);
}
