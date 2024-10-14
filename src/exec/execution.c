/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:27:45 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 10:04:31 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Lecture 0
// Ecriture 1

void	exec_command(t_cmd *command)
{
	if (!*command->bin)
		error_prompt("empty command", 126);
	if (execve(command->bin, ft_lst_to_matrix(command->args),
			get_env_array()) == -1)
		error_prompt("execve error", 1);
}

void	prepare_command(t_cmd *command)
{
	set_redirections(command);
	if (!get_absolute_path(command) || ft_strlen(command->bin) == 0)
		return (command_not_found(command->bin));
	command->bin = get_absolute_path(command);
	ft_lstadd_front(&command->args, gc_lstnew(command->bin));
	if (builtin_bypass(command))
		return (exec_builtin(command));
	data()->pid = fork();
	if (data()->pid == -1)
		error_prefix("fork");
	if (data()->pid == 0)
	{
		init_handlers_child();
		set_io(command);
		close_fds();
		if (is_builtin(command) >= 0)
			exec_builtin(command);
		else
			exec_command(command);
	}
}

void	execute(void)
{
	int		status;
	t_cmd	*command;

	command = data()->command;
	while (command)
	{
		prepare_command(command);
		if (command->heredoc == 1)
			unlink(command->input);
		command = command->next;
	}
	waitpid(-1, &status, 0);
	close_fds();
	set_exit_code(WEXITSTATUS(status));
}
