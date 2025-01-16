/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_enhanced_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:44:44 by marvin            #+#    #+#             */
/*   Updated: 2024/06/13 15:27:06 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(char c, char *sep)
{
	int	x;

	x = 0;
	while (sep[x])
	{
		if (sep[x] == c)
			return (1);
		x++;
	}
	return (0);
}

int	is_in_quote(const char *input, char *c, int y)
{
	while (input[y])
	{
		if (input[y] == '\'')
		{
			y++;
			while (input[y] && input[y] != '\'')
			{
				if (is_sep(input[y], c))
					return (1);
				y++;
			}
		}
		if (input[y] == '\"')
		{
			y++;
			while (input[y] && input[y] != '\"')
			{
				if (is_sep(input[y], c))
					return (1);
				y++;
			}
		}
		y++;
	}
	return (0);
}
