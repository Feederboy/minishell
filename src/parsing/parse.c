/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:40:22 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 04:10:47 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_command(int i)
{
	t_cmd	*last;
	t_cmd	*command;

	last = NULL;
	command = create_command();
	command->index = i;
	if (!data()->command)
	{
		command->prev = NULL;
		command->next = NULL;
		data()->command = command;
	}
	else
	{
		last = data()->command;
		while (last->next != NULL)
			last = last->next;
		last->next = command;
		command->prev = last;
	}
	data()->parsing = NULL;
}

void	extract_quotes(char *cmd, char c)
{
	int		i;
	char	*s;
	t_list	*lst;

	i = 0;
	lst = data()->tmp;
	while (cmd[i] && cmd[i] != c)
		i++;
	data()->line = cmd + i + 1;
	s = gc_strndup(cmd, i);
	if (c == '"')
		s = expand_vars(s);
	if (data()->merge && lst)
		join_previous(s);
	else if (!data()->merge)
		ft_lstadd_back(&data()->parsing, gc_lstnew(s));
}

void	parse_quotes_and_useless_spaces(void)
{
	if (*data()->line == '"' || *data()->line == '\'')
		get_next_quoted_string();
	while (*data()->line && *data()->line == ' ' && data()->line++)
		data()->merge = 0;
}

void	extract_commands(void)
{
	char	*tmp;

	while (*data()->line)
	{
		tmp = gc_strdup("");
		parse_quotes_and_useless_spaces();
		while (*data()->line && !ft_has_char("\"' |", *data()->line))
			tmp = gc_strnjoin(tmp, data()->line++, 1);
		if (!data()->tmp && ft_strlen(tmp))
		{
			data()->tmp = gc_lstnew(expand_vars(tmp));
			ft_lstadd_back(&data()->parsing, data()->tmp);
		}
		else if (ft_strlen(tmp) && data()->merge)
				tmp = join_previous(expand_vars(tmp));
		else if (ft_strlen(tmp))
			ft_lstadd_back(&data()->parsing, gc_lstnew(expand_vars(tmp)));
		if (*data()->line == '|')
		{
			init_command(data()->c_count++);
			data()->line++;
		}
	}
	init_command(data()->c_count++);
}

/*
If first char is #, so a comment, no need to go further
*/
int	parse(void)
{
	if (prompt())
	{
		extract_commands();
		return (1);
	}
	return (0);
}
