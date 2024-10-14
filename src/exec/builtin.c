/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:30:29 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 05:20:38 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (str_equals(cmd->bin, "cd"))
		return (CD);
	if (str_equals(cmd->bin, "exit"))
		return (EXIT);
	if (str_equals(cmd->bin, "unset"))
		return (UNSET);
	if (str_equals(cmd->bin, "export"))
		return (EXPORT);
	if (str_equals(cmd->bin, "echo"))
		return (ECHO);
	if (str_equals(cmd->bin, "env"))
		return (ENV);
	if (str_equals(cmd->bin, "pwd"))
		return (PWD);
	if (str_equals(cmd->bin, "export"))
		return (EXPORT);
	return (-1);
}

void	exec_builtin(t_cmd *cmd)
{
	t_builtin_exec	builtin[8];

	builtin[CD] = &cd;
	builtin[ECHO] = &echo;
	builtin[ENV] = &env;
	builtin[EXIT] = &minishell_exit;
	builtin[EXPORT] = &export_builtin;
	builtin[PWD] = &pwd;
	builtin[UNSET] = &unset;
	if (is_builtin(cmd) != -1)
		return (builtin[is_builtin(cmd)](cmd));
}

int	builtin_bypass(t_cmd *command)
{
	if (str_equals(command->bin, "cd")
		|| str_equals(command->bin, "unset")
		|| str_equals(command->bin, "exit")
		|| (str_equals(command->bin, "export") && command->args->next))
		return (1);
	return (0);
}
