/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:54:24 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 10:21:39 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redirections(t_cmd *cmd)
{
	if (cmd->input)
		cmd->fdin = file_open(cmd->input, READ_MODE);
	if (cmd->output && cmd->append)
		cmd->fdout = file_open(cmd->output, APPEND_MODE);
	if (cmd->output && !cmd->append)
		cmd->fdout = file_open(cmd->output, TRUNCATE_MODE);
	if (cmd->next && (!cmd->output || cmd->fdout == 1))
	{
		if (pipe(cmd->pipe) == -1)
			error_prompt("pipe error", 1);
		cmd->pipout = cmd->pipe[1];
		cmd->next->pipin = cmd->pipe[0];
	}
}

void	set_io(t_cmd *cmd)
{
	if (cmd->fdin != STDIN_FILENO)
	{
		closep(0, cmd->index);
		dup2(cmd->fdin, STDIN_FILENO);
	}
	else if (cmd->pipin != -1)
	{
		closep(0, cmd->index);
		dup2(cmd->pipin, STDIN_FILENO);
	}
	if (cmd->fdout != STDOUT_FILENO)
	{
		closep(1, cmd->index);
		dup2(cmd->fdout, STDOUT_FILENO);
	}
	else if (cmd->pipout != -1)
	{
		closep(1, cmd->index);
		dup2(cmd->pipout, STDOUT_FILENO);
	}
}
