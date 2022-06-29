/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:40:22 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 05:36:57 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char *key, char *value)
{
	t_env	*env;

	env = data()->env;
	if (get_env(key) != NULL)
	{
		while (env && !str_equals(env->key, key))
			env = env->next;
		env->value = gc_strdup(value);
	}
	else
	{
		add_env_list(&data()->env,
			create_env_list(gc_strjoin(gc_strjoin(key, "="), value)));
	}
}

/* Get a variable from environment */
char	*get_env(char *key)
{
	t_env	*env;

	env = data()->env;
	while (env != NULL)
	{
		if (str_equals(env->key, gc_strdup(key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	add_env_list(t_env **env, t_env *next)
{
	t_env	*last;

	last = NULL;
	if (!next)
		return ;
	if (!*env)
	{
		*env = next;
		return ;
	}
	last = *env;
	while (last && last->next)
		last = last->next;
	last->next = next;
}

t_env	*create_env_list(char *env)
{
	t_env	*envl;
	char	**s;

	envl = (t_env *)gc_malloc(sizeof(t_env));
	if (!envl)
		return (NULL);
	s = gc_split(env, '=');
	envl->key = s[0];
	if (ft_matrix_len(s) > 1)
	{
		envl->value = str_join_recursive(&s[1], "=");
	}
	else
	{
		envl->value = s[1];
	}
	envl->next = NULL;
	return (envl);
}

void	init_env(char	**envp)
{
	t_env		*env;
	t_env		*last;

	last = NULL;
	while (*envp)
	{
		env = create_env_list(*envp++);
		if (!last)
			data()->env = env;
		else
			last->next = env;
		last = env;
	}
	if (data()->env_init == 0)
		set_defaults_env();
}
