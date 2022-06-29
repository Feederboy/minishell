/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 01:48:29 by matt              #+#    #+#             */
/*   Updated: 2022/06/29 02:53:54 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_cmd *cmd)
{
	t_env	*prev;
	t_env	*env;

	env = data()->env;
	cmd->args = cmd->args->next;
	while (env)
	{
		if (!str_equals(env->key, cmd->args->content))
		{
			prev = env;
			env = env->next;
			continue ;
		}
		prev->next = env->next;
		break ;
	}
	set_exit_code(1);
}
