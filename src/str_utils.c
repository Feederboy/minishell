/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:40:22 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/28 23:22:13 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if two strings are equals */
int	is_allowed_redir_name(char *s)
{
	while (*s)
	{
		if (ft_isalnum(*s))
		{
			s++;
			continue ;
		}
		if (*s == '$')
		{
			s++;
			continue ;
		}
		return (0);
	}
	return (1);
}

/* Check if two strings are equals */
int	str_equals(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((s1[i] - s2[i]) == 0);
}

// Join multiple string with an optionnal separator between (COULD BE NULL)
char	*str_join_recursive(char **strs, char *sep)
{
	char	*s;

	s = gc_strdup("");
	if (!sep)
		sep = s;
	while (*strs)
	{
		if (*(strs + 1) == NULL)
			sep = gc_strdup("");
		s = gc_strjoin(s, gc_strjoin(*strs++, sep));
	}
	return (s);
}

char	*trim_space(char *s)
{
	char	*res;
	int		squote;
	int		dquote;

	squote = 0;
	dquote = 0;
	res = gc_strdup("");
	while (*s)
	{
		if (ft_has_char("\t ", *s) && !squote && !dquote)
		{
			s++;
			if (ft_strlen(res) && res[ft_strlen(res) - 1] != ' ')
				res = gc_strnjoin(res, " ", 1);
			continue ;
		}
		if (*s == '\'')
			squote = !squote;
		if (*s == '"')
			dquote = !dquote;
		res = gc_strnjoin(res, s, 1);
		s++;
	}
	return (res);
}
