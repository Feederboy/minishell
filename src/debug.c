/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:40:22 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/28 23:21:19 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	ft_printf_fd(1, "DEBUG ENV\n");
	while (env)
	{
		ft_printf_fd(1, "%s=%s\n", env->key, env->value);
		env = env->next;
	}
	ft_printf_fd(1, "END DEBUG ENV\n");
}

void	print_lst(t_list *lst, char *name)
{
	int	i;

	ft_printf_fd(1, "=============\nSTART %s\n=============\n", name);
	i = 0;
	while (lst)
	{
		ft_printf_fd(1, "[%i] %s\n", i, lst->content);
		i++;
		lst = lst->next;
	}
	ft_printf_fd(1, "=============\nEND %s\n=============\n", name);
}

void	print_matrix(char **s)
{
	int	i;

	i = 0;
	ft_printf_fd(1, "DEBUG MATRIX\n");
	while (s[i])
	{
		ft_printf_fd(1, "[%i] %s\n", i, s[i]);
		i++;
	}
	ft_printf_fd(1, "END DEBUG MATRIX\n");
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	printf("command->index       | %d\n", cmd->index);
	printf("command->bin         | %s\n", cmd->bin);
	printf("command->builtin     | %d\n", cmd->builtin);
	printf("command->pipe        | %d %d\n", cmd->pipe[1], cmd->pipe[0]);
	printf("command->input > fd  | %s > %d\n", cmd->input, cmd->fdin);
	printf("command->heredoc     | %d\n", cmd->heredoc);
	printf("command->output > fd | %s > %d\n", cmd->output, cmd->fdout);
	printf("command->append      | %d\n", cmd->append);
	if (cmd->next)
		printf("command->next      | %d\n", cmd->next->index);
	if (cmd->prev)
		printf("command->prev      | %d\n", cmd->prev->index);
	print_lst(cmd->args, "ARGS");
}
