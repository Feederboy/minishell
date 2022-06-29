/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 02:20:38 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/28 23:55:56 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print a string to stdout */
void	env(t_cmd *cmd)
{
	char	**envp;

	envp = get_env_array();
	while (*envp)
	{
		write(cmd->fdout, *envp, ft_strlen(*envp));
		write(cmd->fdout, "\n", 1);
		envp++;
	}
	set_exit_code(0);
	clean_exit();
}
