/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:22 by leoherna          #+#    #+#             */
/*   Updated: 2024/03/06 14:13:22 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	defined_or_undefined(char *command)
{
	int	i;
	int	defined;
	int	undefined;

	defined = 1;
	undefined = 0;
	i = 0;
	if (command[0] == '=')
		return (-1);
	while (command[i] != '\0')
	{
		if (command[i] == '=')
			return (defined);
		if (!((command[i] >= 'A' && command[i] <= 'Z')
				|| (command[i] >= 'a' && command[i] <= 'z')))
			return (-1);
		i++;
	}
	return (undefined);
}

void	export_cmd(t_mini *mini, char *cmd)
{
	char	**command;
	int		i;

	i = 1;
	command = ft_split(cmd, " ", 0);
	if (!command[1])
	{
		export_env_cmd(mini);
		free_tab(command);
		return ;
	}
	while (command[i] != NULL)
	{
		if (defined_or_undefined(command[i]) == 1)
			defined_function(mini, command, i);
		else if (defined_or_undefined(command[i]) == 0)
			undefined_function(mini, command, i);
		else
		{
			printf("-bash: export: `%s': not a valid identifier\n", command[i]);
			g_sig_error_code = 1;
		}
		i++;
	}
	free_tab(command);
}
