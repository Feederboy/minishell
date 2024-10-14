/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:54:24 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 10:28:58 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_not_found(char *s)
{
	data()->pid = fork();
	if (data()->pid == 0)
	{
		error_prompt(gc_strjoin(
				gc_strjoin("minishell: ", s), ": command not found"), 127);
		clean_exit();
	}
}

void	close_fds(void)
{
	t_cmd	*command;

	command = data()->command;
	while (command)
	{
		close_fd_command(command);
		command = command->next;
	}
}

void	close_fd_command(t_cmd *cmd)
{
	if (cmd->pipin != -1)
		closep(cmd->pipin, cmd->index);
	if (cmd->pipout != -1)
		closep(cmd->pipout, cmd->index);
	if (cmd->fdin != 0)
		closep(cmd->fdin, cmd->index);
	if (cmd->fdout != 1)
		closep(cmd->fdout, cmd->index);
}

void	set_exit_code(int code)
{
	data()->last_exit_code = code;
	set_env("?", gc_itoa(data()->last_exit_code));
}

void	closep(int fd, int i)
{
	(void)i;
	close(fd);
}
