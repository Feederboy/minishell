/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 02:20:38 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 02:58:49 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_env(t_cmd *cmd, char **env)
{
	char	**str;

	while (*env)
	{
		str = gc_split(*env, '=');
		write(cmd->fdout, gc_strjoin("export ", str[0]),
			ft_strlen(gc_strjoin("export ", str[0])));
		if (ft_matrix_len(str) > 1)
		{
			write(cmd->fdout, "=\"", 2);
			write(cmd->fdout, str_join_recursive(&str[1], "="),
				ft_strlen(str_join_recursive(&str[1], "=")));
			write(cmd->fdout, "\"", 1);
		}
		write(cmd->fdout, "\n", 1);
		env++;
	}
}

void	export_error(char *key)
{
	if (key)
		ft_printf_fd(2, "export: `%s': not a valid identifier\n", key);
	else
		ft_printf_fd(2, "export: `': not a valid identifier\n");
	set_exit_code(1);
}

/* Print a string to stdout */
void	export_builtin(t_cmd *cmd)
{
	char	**str;
	char	*key;
	char	*value;

	cmd->args = cmd->args->next;
	if (cmd->args && cmd->args->content)
	{
		str = gc_split(cmd->args->content, '=');
		key = str[0];
		if (!is_valid_key(key))
			return (export_error(key));
		value = gc_strdup("");
		if (ft_matrix_len(str) > 1)
			value = str_join_recursive(&str[1], "=");
		set_env(key, value);
		set_exit_code(0);
	}
	else
	{
		list_env(cmd, get_env_array());
		set_exit_code(0);
		clean_exit();
	}
}
