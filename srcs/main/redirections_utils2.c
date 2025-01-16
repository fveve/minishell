/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:52:11 by arafa             #+#    #+#             */
/*   Updated: 2024/06/11 14:53:40 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_double(char	*input)
{
	int	x;

	x = 0;
	while (input[x] && input[x] != '<' && input[x] != '>')
		x++;
	if (input[x + 1])
	{
		if (input[x + 1] == '>' || input[x + 1] == '<')
			return (1);
	}
	return (0);
}
