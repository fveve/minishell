/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:50:04 by arafa             #+#    #+#             */
/*   Updated: 2024/06/11 13:49:10 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_nb(char	***env, char **str, int x, int y)
{
	char	*temp;

	temp = NULL;
	(*env)[x][y] = '\0';
	temp = ft_strjoin((*env)[x], *str);
	free((*env)[x]);
	(*env)[x] = ft_strdup(temp);
	free(temp);
	free(*str);
}

void	change_shell_level(char	***env)
{
	char	*str;
	int		nb;
	int		x;
	int		y;

	x = 0;
	y = 0;
	str = NULL;
	while ((*env)[x] && ft_strncmp((*env)[x], "SHLVL=", 6))
		x++;
	if ((*env)[x] && !ft_strncmp((*env)[x], "SHLVL=", 6))
	{
		while ((*env)[x][y] && ((*env)[x][y] < '0' || (*env)[x][y] > '9'))
			y++;
		if ((*env)[x][y] <= '9' && (*env)[x][y] >= '0')
		{
			nb = ft_atoi(&(*env)[x][y]);
			nb++;
			str = ft_itoa(nb);
			replace_nb(env, &str, x, y);
		}
	}
}
