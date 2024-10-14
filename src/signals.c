/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:01:11 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 05:30:08 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int code)
{
	if (data()->pid == -1 && code == SIGINT)
	{
		set_exit_code(128 + SIGINT);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_handler(int code)
{
	char	*nbr;

	nbr = gc_itoa(code);
	if (data()->pid == 0)
	{
		ft_putstr_fd("\nQuit (core dumped)\n", STDERR_FILENO);
		set_exit_code(128 + code);
		clean_exit();
	}
}

void	init_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_handlers_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
