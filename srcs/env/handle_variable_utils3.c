/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:05:46 by leoherna          #+#    #+#             */
/*   Updated: 2024/05/29 15:05:46 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_varlen(char *command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '$')
		{
			i++;
			while (command[i] != '\0' && command[i] != ' ')
			{
				i++;
				j++;
			}
			return (j);
		}
		i++;
	}
	return (-1);
}

void	init_logname(t_mini *mini)
{
	char	*variable;
	int		which_line;

	variable = "LOGNAME";
	which_line = check_if_exist_handle(mini, variable);
	if (which_line != -1)
	{
		mini->logname = search_value(mini, which_line);
	}
}

char	*dollar_found(int i, int j, char *command, char *variable)
{
	i++;
	if (command[i] == '\0' || command[i] == ' '
		|| command[i] == '\"' || command[i] == '/')
		return (NULL);
	variable = malloc (sizeof(char) * (get_varlen(command) + 1));
	while (command[i] != '\0'
		&& command[i] != ' ' && command[i] != '\"' && command[i] != '/')
	{
		variable[j] = command[i];
		i++;
		j++;
	}
	variable[j] = '\0';
	return (variable);
}
