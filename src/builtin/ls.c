/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ls.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:49:16 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/05 15:46:24 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(char *command, char *option, char **envp)
{
	char	*cmd_path;
	char	*options[3] = {"ls", "-la", NULL};

	(void)option;
	cmd_path = get_executable_path(command);
	if (!cmd_path)
		return ;
	execve(cmd_path, options, envp);
	free(cmd_path);
}
