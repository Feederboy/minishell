/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freematrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:33:18 by mguerra           #+#    #+#             */
/*   Updated: 2022/05/03 08:12:38 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(char **s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}
