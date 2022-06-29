/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:40:22 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/28 23:08:11 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_io(t_cmd *cmd, char c, int next)
{
	char	*tmp;
	char	rev;
	t_list	*lst;

	lst = data()->parsing;
	if (next)
		lst = lst->next;
	tmp = (char *)lst->content;
	if (c == '<')
		rev = '>';
	else
		rev = '<';
	if (ft_has_char(tmp, rev))
	{
		tmp = gc_split(tmp, rev)[0];
		while (*(char *)lst->content && *(char *)lst->content != rev)
			lst->content++;
		parse_io(cmd, rev);
	}
	while (tmp && (*tmp == '>' || *tmp == '<'))
		tmp++;
	return (tmp);
}

void	parse_io(t_cmd *cmd, char c)
{
	int		i;
	char	*tmp;
	t_list	*lst;

	lst = data()->parsing;
	tmp = (char *)lst->content;
	i = 0;
	if (ft_strlen(tmp) == 1 && lst->next)
		(parse_redirections(cmd, check_io(cmd, c, 1), c, 0), go_next(2));
	if (ft_strlen(tmp) == 2 && lst->next && *(tmp + 1) == c)
		(parse_redirections(cmd, check_io(cmd, c, 1), c, 1), go_next(2));
	if (ft_strlen(tmp) > 1 && *(tmp + 1) != c)
		(parse_redirections(cmd, check_io(cmd, c, 0), c, 0), go_next(1));
	if (ft_strlen(tmp) > 2 && *(tmp + 1) == c)
		(parse_redirections(cmd, check_io(cmd, c, 0), c, 0), go_next(1));
}

void	extract_data(t_cmd *cmd)
{
	t_list	*lst;
	char	*tmp;

	lst = NULL;
	while (data()->parsing)
	{
		tmp = (char *)data()->parsing->content;
		if (*tmp && (*tmp == '<' || *tmp == '>'))
		{
			parse_io(cmd, *tmp);
			continue ;
		}
		if (!cmd->bin && *tmp && *tmp != '<' && *tmp != '>')
		{
			cmd->bin = tmp;
			data()->parsing = data()->parsing->next;
			continue ;
		}
		if (cmd->bin && tmp && *tmp != '<' && *tmp != '>')
		{
			lst = gc_lstnew(tmp);
			ft_lstadd_back(&cmd->args, lst);
		}
		data()->parsing = data()->parsing->next;
	}
}

t_cmd	*create_command(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)gc_malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->index = 0;
	cmd->args = NULL;
	cmd->input = NULL;
	cmd->fdin = STDIN_FILENO;
	cmd->heredoc = 0;
	cmd->pipin = -1;
	cmd->output = NULL;
	cmd->fdout = STDOUT_FILENO;
	cmd->append = 0;
	cmd->pipout = -1;
	cmd->bin = NULL;
	cmd->builtin = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	extract_data(cmd);
	if (cmd->heredoc == 1)
		heredoc(cmd);
	return (cmd);
}
