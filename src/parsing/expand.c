/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:40:22 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 03:20:53 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key(char *s)
{
	if (!s)
		return (0);
	if (ft_isdigit(*s))
		return (0);
	while (*s)
	{
		if (ft_isalnum(*s) && s++)
			continue ;
		if (*s == '_' && s++)
			continue ;
		if (*s == '?' && s++)
			continue ;
		return (0);
	}
	return (1);
}

char	*expand_vars(char *s)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	res = gc_strdup("");
	while (s[i])
	{
		if (s[i] && s[i] == '$')
		{
			tmp = gc_strdup("");
			if (ft_has_char(" \0", s[++i]))
				res = gc_strjoin(res, gc_strdup("$"));
			tmp = get_env_key(&s[i]);
			if (is_valid_key(tmp) && get_env(tmp))
				res = gc_strjoin(res, get_env(tmp));
			if (is_valid_key(tmp))
				i += ft_strlen(tmp);
		}
		if (s[i] == '$')
			continue ;
		if (s[i])
			res = gc_strjoin(res, gc_strndup(&s[i++], 1));
	}
	return (res);
}

char	*replace_vars(char *s)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	res = gc_strdup("");
	tmp = gc_strdup("");
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				res = gc_strnjoin(res, &s[i++], 1);
			i++;
		}
		while (s[i] && s[i] != '\'')
			tmp = gc_strnjoin(tmp, &s[i++], 1);
		if (ft_strlen(tmp))
		{
			res = gc_strjoin(res, expand_vars(tmp));
			tmp = gc_strdup("");
		}
	}
	return (res);
}

void	expand(void)
{
	t_data	*d;
	t_cmd	*cmd;
	t_list	*lst;
	t_list	*prev;

	d = data();
	cmd = d->command;
	while (cmd)
	{
		if (cmd->input)
			cmd->input = replace_vars(cmd->input);
		if (cmd->output)
			cmd->output = replace_vars(cmd->output);
		cmd->bin = replace_vars(cmd->bin);
		lst = cmd->args;
		prev = NULL;
		while (lst)
		{
			lst->content = replace_vars(lst->content);
			prev = lst;
			lst = lst->next;
		}
		cmd = cmd->next;
	}
}
