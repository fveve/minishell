/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:19:16 by arafa             #+#    #+#             */
/*   Updated: 2024/06/03 14:51:27 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	already_defined(t_mini *mini, char **commands, int i);

char	**add_env_variable(t_mini *mini, char *new_env_var);

void	change_env(t_mini *mini, char **almostnewenv);

char	**return_new_export_env(t_mini *mini, char *new_env_var);

char	**return_new_export_env(t_mini *mini, char *new_env_var);

char	**get_export_env_one_line_unset2(t_mini *mini, char *env_to_remove)
{
	char	*env_one_line;
	char	*temp;
	int		i;

	i = 1;
	env_one_line = ft_strjoin(mini->export_env[0], " ");
	while (i != ft_strlen2(mini->export_env))
	{
		if (ft_strncmp(mini->export_env[i], env_to_remove,
				ft_strlen(env_to_remove)) == 0)
		{
			i++;
		}
		else
		{
			temp = ft_strjoin(env_one_line, " ");
			free(env_one_line);
			env_one_line = ft_strjoin(temp, mini->export_env[i]);
			free(temp);
			i++;
		}
	}
	return (free_export_unset(env_one_line));
}

void	defined_function2(t_mini *mini, char **command, int i)
{
	char	**new_env;
	char	**new_export_env;

	new_export_env = NULL;
	new_env = NULL;
	already_defined(mini, command, i);
	new_env = add_env_variable(mini, command[i]);
	change_env(mini, new_env);
	new_export_env = return_new_export_env(mini, command[i]);
	change_export_env(mini, new_export_env);
	free_tab(new_env);
	free_tab(new_export_env);
}
