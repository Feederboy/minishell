/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:54:24 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 10:28:38 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_fd(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		error_prefix("dup2");
}

static int	validate(char *s)
{
	if (!ft_strcmp(s, ".") || !ft_strcmp(s, "..") || !ft_strcmp(s, "../")
		|| !ft_strcmp(s, "./"))
		return (0);
	if (!get_env("PATH"))
		return (ft_printf_fd(2, "No PATH variable. Aborting...\n"), 0);
	return (1);
}

char	*try_paths(char *s)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = gc_split(get_env("PATH"), ':');
	if (!paths)
		error_prompt("split error", 1);
	i = 0;
	while (paths[i])
	{
		tmp = gc_strjoin(paths[i++], gc_strjoin("/", s));
		if (access(tmp, F_OK) == 0)
			return (tmp);
	}
	return (NULL);
}

char	*check_relative(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	if (*s == '.')
	{
		if (ft_strlen(s) > 2)
			while (!ft_strncmp(s, "./", 2))
				s += 2;
		if (ft_strlen(s) > 3)
			while (!ft_strncmp(s, "../", 3))
				s += 3;
		tmp = gc_strjoin(get_env("PWD"), gc_strjoin("/", s));
		if (access(tmp, F_OK) != 0)
			return (error_prompt("This program does not exists.", 127), NULL);
		if (access(tmp, X_OK) != 0)
			return (error_prompt("permission denied", 126), NULL);
		return (tmp);
	}
	return (NULL);
}

char	*get_absolute_path(t_cmd *cmd)
{
	char	*s;

	s = cmd->bin;
	if (!s)
		return (NULL);
	if (validate(s) || is_builtin(cmd) >= 0)
	{
		if (is_builtin(cmd) >= 0)
			return (s);
		if (check_relative(s))
			return (check_relative(s));
		return (try_paths(s));
	}
	return (NULL);
}
