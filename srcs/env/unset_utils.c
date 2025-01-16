/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:35:21 by leoherna          #+#    #+#             */
/*   Updated: 2024/05/15 10:35:21 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_export_env_one_line_unset(t_mini *mini, char *env_to_remove)
{
	char	*env_one_line;
	char	*temp;
	int		i;

	i = 1;
	env_one_line = ft_strjoin(mini->export_env[0], " ");
	while (i != ft_strlen2(mini->env))
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

char	**get_env_one_line_unset(t_mini *mini, char *env_to_remove)
{
	char	*env_one_line;
	char	*temp;
	int		i;

	i = 1;
	env_one_line = ft_strjoin(mini->env[0], " ");
	while (i != ft_strlen2(mini->env))
	{
		if (ft_strncmp(mini->env[i], env_to_remove,
				ft_strlen(env_to_remove)) == 0)
		{
			i++;
		}
		else
		{
			temp = ft_strjoin(env_one_line, " ");
			free(env_one_line);
			env_one_line = ft_strjoin(temp, mini->env[i]);
			free(temp);
			i++;
		}
	}
	return (free_export_unset(env_one_line));
}

void	remove_export_variable_unset(t_mini *mini, char **command, int i)
{
	char	**new_export_env;

	if (does_var_exist2(mini, command[i]) == 1)
	{
		new_export_env = get_env_one_line_unset(mini, command[i]);
		change_export_env(mini, new_export_env);
		free_tab(new_export_env);
	}
}
