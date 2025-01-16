/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager_utils4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:08:27 by arafa             #+#    #+#             */
/*   Updated: 2024/06/11 15:09:53 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_redirection5(char *input, int trigger, int x)
{
	while (input[x])
	{
		if (input[x] != '>' && input[x] != '<')
			trigger = 0;
		if (input[x] == '>' || input[x] == '<')
			trigger++;
		if (trigger > 2)
		{
			printf("Redirection problem\n");
			return (1);
		}
		x++;
	}
	return (0);
}

int	verify_cmd4(char *input, int x, char **tab)
{
	x = 1;
	if (!tab || (ft_countwords(input, " ", &x) > 1 && just_space(tab[0], 0)))
	{
		free_tab(tab);
		return (1);
	}
	free_tab(tab);
	return (0);
}
