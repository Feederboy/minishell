/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 02:20:38 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/28 22:57:54 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_new_line_flag(char *s)
{
	if (s[0] != '-' || s[1] != 'n')
		return (0);
	s = s + 2;
	while (*s == 'n')
		s++;
	return (*s == '\0');
}

/* Print a string to stdout 
new_line=0 if echo -n blabla
new_line=1 if echo blabla
*/
void	echo(t_cmd *cmd)
{
	int	new_line;

	new_line = 1;
	cmd->args = cmd->args->next;
	while (cmd->args && is_new_line_flag((char *)cmd->args->content))
	{
		new_line = 0;
		cmd->args = cmd->args->next;
	}
	while (cmd->args)
	{
		write(cmd->fdout, (char *)cmd->args->content,
			ft_strlen((char *)cmd->args->content));
		if (cmd->args->next)
			write(cmd->fdout, " ", 1);
		cmd->args = cmd->args->next;
	}
	if (new_line)
		write(cmd->fdout, "\n", 1);
	set_exit_code(0);
	clean_exit();
}
