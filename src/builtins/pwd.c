/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:31:57 by matt              #+#    #+#             */
/*   Updated: 2022/06/28 23:01:25 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_cmd *cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf_fd(2, "%s\n", PWD_ERROR);
		set_exit_code(1);
	}
	else
	{
		printf("%s\n", cwd);
		set_exit_code(0);
	}
	free(cwd);
	clean_exit();
}
