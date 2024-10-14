/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:40:22 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 04:35:31 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_vars_heredoc(char *s)
{
	char	*res;
	char	*tmp;
	int		i;
	int		end;

	i = 0;
	end = ft_strlen(s) - 1;
	res = gc_strdup("");
	tmp = gc_strdup("");
	while (s[i])
	{
		if (s[i] && s[i] == '$')
		{
			i++;
			while (s[i] && !ft_has_char("$ '\"\n", s[i]))
				tmp = gc_strjoin(tmp, gc_strndup(&s[i++], 1));
			if (get_env(tmp))
				res = gc_strjoin(res, get_env(tmp));
			tmp = gc_strdup("");
		}
		if (s[i] != '$' || (s[i] == '$'
				&& (ft_has_char("\n ", s[i + 1]) || s[i + 1] == '\0')))
			res = gc_strjoin(res, gc_strndup(&s[i++], 1));
	}
	return (res);
}

void	heredoc(t_cmd *cmd)
{
	char	*line;
	char	*buffer;
	int		eof;
	int		fd;

	buffer = gc_strdup("");
	eof = 0;
	while (!eof)
	{
		line = readline("> ");
		eof = ft_strncmp(line, cmd->input, ft_strlen(cmd->input)) == 0;
		if (!eof)
			buffer = gc_strjoin(buffer, gc_strjoin(line, "\n"));
	}
	line = gc_strjoin(".heredoc_", gc_itoa(eof++));
	while (access(line, F_OK) != -1 && eof < 1024)
		line = gc_strjoin(".heredoc_", gc_itoa(eof++));
	if (eof >= 1024)
		error_prompt("Too much heredoc present", 1);
	fd = file_open(line, TRUNCATE_MODE);
	ft_putstr_fd(expand_vars_heredoc(buffer), fd);
	cmd->input = line;
	close(fd);
}
