/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 14:16:31 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/21 16:02:24 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

static void	handle_crtl_c(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
	printf("ctrl-c\n");
}

void	init_signal_handler(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_cflag = ECHOCTL;
	signal(SIGINT, handle_crtl_c);
}
