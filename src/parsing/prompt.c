/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:40:22 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 10:08:37 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt_gnl(void)
{
	ft_putstr_fd(PROMPT, 2);
	data()->line = gc_get_next_line(0);
	if (data()->line == NULL)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		clean_exit();
	}
	if (!data()->line || ft_strlen(data()->line) == 0
		|| *data()->line == '#')
		return (0);
	return (1);
}

int	prompt(void)
{
	char	*s;

	s = readline(PROMPT);
	if (s)
	{
		data()->line = gc_strdup(s);
		free(s);
	}
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		clean_exit();
	}
	while (data()->line && *data()->line == ' ')
		data()->line++;
	if (!data()->line || ft_strlen(data()->line) == 0
		|| *data()->line == '#')
		return (0);
	add_history(data()->line);
	return (1);
}
