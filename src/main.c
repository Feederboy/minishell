/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:00:54 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 10:08:44 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset(void)
{
	char	**env;

	env = get_env_array_ft();
	waitpid(-1, NULL, 0);
	data()->init = 0;
	gc_clear();
	init_env(env);
	ft_free_matrix(env);
	rl_reset_line_state();
}

static void	init(void)
{
	extern char	**environ;

	data()->env_init = 0;
	init_env(environ);
	data()->env_init = 1;
}

static void	loop(void)
{
	init();
	rl_outstream = stderr;
	while (42)
	{
		waitpid(-1, NULL, 0);
		init_handlers();
		if (parse())
		{
			execute();
			if (ft_strncmp(data()->line, "exit", 5) == 0
				&& (data()->line[4] == '\0' || data()->line[4] == ' '))
				(clean_exit());
		}
		reset();
	}
}

static void	header_message(void)
{
	int		fd;
	char	*line;

	fd = open(".header", O_RDONLY, 0600);
	line = NULL;
	if (fd < 0)
		return ;
	line = gc_get_next_line(fd);
	while (line)
	{
		ft_printf_fd(2, "%s", line);
		line = gc_get_next_line(fd);
	}
	close(fd);
}

int	main(int ac, char **av)
{
	(void)ac;
	data()->av = av;
	header_message();
	loop();
	return (0);
}
