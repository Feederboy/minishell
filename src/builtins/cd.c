/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 02:20:38 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 04:33:43 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_cwd(void)
{
	char	*cwd;

	set_env("OLDPWD", get_env("PWD"));
	cwd = getcwd(NULL, 0);
	set_env("PWD", cwd);
	free(cwd);
}

/* Change current working directory */
void	cd(t_cmd *cmd)
{
	char	*path;

	cmd->args = cmd->args->next;
	if (!cmd->args)
		path = get_env("HOME");
	else if (*(char *)cmd->args->content == '~')
		path = gc_strjoin(get_env("HOME"), (char *)cmd->args->content + 1);
	else
		path = cmd->args->content;
	if (access(path, F_OK) == -1)
		return (error_prompt("No such file or directory\n", 1));
	if (access(path, X_OK) == -1)
		return (error_prompt("permission denied\n", 1));
	if (chdir(path) == -1)
		return (error_prompt("chdir error\n", 1));
	update_cwd();
	set_exit_code(errno);
}
