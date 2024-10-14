/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:01:52 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 10:21:40 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_next(int i)
{
	while (i--)
	{
		if (data()->parsing)
			data()->parsing = data()->parsing->next;
	}
}

t_data	*data(void)
{
	static t_data	data;

	if (data.init != 1)
	{
		data.line = NULL;
		data.commands = NULL;
		data.command = NULL;
		data.env_init = 1;
		data.merge = 1;
		data.tmpcmd = NULL;
		data.parsing = NULL;
		data.prev = NULL;
		data.line = NULL;
		data.env = NULL;
		data.tmp = NULL;
		data.merge = 0;
		data.c_count = 0;
		data.pid = -1;
		data.init = 1;
	}
	return (&data);
}

int	file_open(char *file, int flag)
{
	int	fd;

	fd = 0;
	if (flag == READ_MODE)
		fd = open(file, O_RDONLY | O_CLOEXEC);
	if (flag == APPEND_MODE)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0644);
	if (flag == TRUNCATE_MODE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
	if (fd == -1)
		error_file(file);
	return (fd);
}

void	get_next_quoted_string(void)
{
	extract_quotes(data()->line + 1, *data()->line);
	if (*data()->line && !ft_has_char(" |", *data()->line))
		data()->merge = 1;
}

char	*join_previous(char *s)
{
	t_list	*lst;

	lst = ft_lstlast(data()->tmp);
	lst->content = gc_strjoin(lst->content, s);
	data()->merge = 0;
	return (gc_strdup(""));
}
