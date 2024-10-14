/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:40:22 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 02:38:04 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_key(char *s)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = gc_strndup(&s[i++], 1);
	while (s[i] && is_valid_key(tmp))
		tmp = gc_strjoin(tmp, gc_strndup(&s[i++], 1));
	if (is_valid_key(tmp))
		return (tmp);
	if (is_valid_key(gc_substr(tmp, 0, ft_strlen(tmp) - 1)))
		return (gc_substr(tmp, 0, ft_strlen(tmp) - 1));
	return (gc_strdup(""));
}

void	set_defaults_env(void)
{
	char		*cwd;

	set_env("?", "0");
	if (get_env("SHLVL"))
		set_env("SHLVL", gc_itoa(ft_atoi(get_env("SHLVL")) + 1));
	else
		set_env("SHLVL", "2");
	if (! get_env("PATH"))
		(printf(DEFAULT_PATH_MSG), set_env("PATH", DEFAULT_PATH));
	if (! get_env("PWD"))
	{
		cwd = getcwd(NULL, 0);
		set_env("PWD", cwd);
		free(cwd);
	}
}

int	count_env(t_env *lst)
{
	int		i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**get_env_array(void)
{
	char	**res;
	t_env	*tmp;
	int		i;

	tmp = data()->env;
	res = gc_malloc(sizeof(char *) * (count_env(data()->env) + 1));
	res[count_env(data()->env)] = NULL;
	i = 0;
	while (tmp)
	{
		if (!tmp->value)
			tmp->value = gc_strdup("");
		res[i] = gc_strjoin(tmp->key, gc_strjoin("=", tmp->value));
		i++;
		tmp = tmp->next;
	}
	return (res);
}

char	**get_env_array_ft(void)
{
	char	**res;
	char	*stmp;
	t_env	*tmp;
	int		i;

	tmp = data()->env;
	stmp = NULL;
	res = malloc(sizeof(char *) * (count_env(data()->env) + 1));
	res[count_env(data()->env)] = NULL;
	i = 0;
	while (tmp)
	{
		stmp = ft_strjoin(tmp->key, "=");
		res[i] = ft_strjoin(stmp, tmp->value);
		free(stmp);
		i++;
		tmp = tmp->next;
	}
	return (res);
}
