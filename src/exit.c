/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:40:22 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 04:31:36 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(void)
{
	clear_history();
	close_fds();
	gc_clear();
	close(0);
	close(1);
	close(2);
	exit(data()->last_exit_code);
}

void	error_prompt(char *s, int code)
{
	ft_printf_fd(2, s);
	ft_printf_fd(2, "\n");
	set_exit_code(code);
}

void	error_prefix(char *s)
{
	perror(s);
}

void	error_file(char*s)
{
	perror(s);
}
