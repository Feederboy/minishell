/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:05:16 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/28 23:21:05 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_append_mode(t_cmd *cmd, char *s, int mode)
{	
	cmd->append = mode;
	cmd->output = gc_strdup(s);
}

void	set_heredoc_mode(t_cmd *cmd, char *s, int mode)
{	
	cmd->heredoc = mode;
	cmd->input = gc_strdup(s);
}

void	parse_redirections(t_cmd *cmd, char *s, char c, int mode)
{
	if (c == '>')
		set_append_mode(cmd, s, mode);
	else if (c == '<')
		set_heredoc_mode(cmd, s, mode);
}
