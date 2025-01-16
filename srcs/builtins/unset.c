/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:26:23 by leoherna          #+#    #+#             */
/*   Updated: 2024/02/27 10:26:23 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	value_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == '=')
			return (i);
	}
	return (-1);
}

int	does_var_exist(t_mini *mini, char *env_to_remove)
{
	int	i;

	i = 0;
	while (i < ft_strlen2(mini->env))
	{
		if (ft_strncmp(mini->env[i], env_to_remove,
				value_len(mini->env[i])) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	does_var_exist2(t_mini *mini, char *env_to_remove)
{
	int	i;

	i = 0;
	while (i < ft_strlen2(mini->export_env))
	{
		if (ft_strncmp(mini->export_env[i], env_to_remove,
				ft_strlen(env_to_remove)) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static void	change_env(t_mini *mini, char **new_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	free_tab(mini->env);
	mini->env = malloc(sizeof(char *) * (ft_strlen2(new_env) + 1));
	while (new_env[j] != NULL)
	{
		mini->env[j] = malloc (sizeof(char) * (ft_strlen(new_env[j]) + 1));
		while (new_env[j][i] != '\0')
		{
			mini->env[j][i] = new_env[j][i];
			i++;
		}
		mini->env[j][i] = '\0';
		i = 0;
		j++;
	}
	mini->env[j] = NULL;
}

void	unset_cmd(t_mini *mini, char *cmd)
{
	char	**command;
	char	**new_env;
	int		i;

	i = 1;
	command = ft_split(cmd, " ", 0);
	if (!command[1])
		return ;
	while (command[i] != NULL)
	{
		if (does_var_exist(mini, command[i]) > 0)
		{
			new_env = get_env_one_line_unset(mini, command[i]);
			change_env(mini, new_env);
			remove_export_variable_unset(mini, command, i);
			free_tab(new_env);
		}
		else if (does_var_exist(mini, command[i]) == 0)
		{
			g_sig_error_code = 1;
			printf("-bash: export: `%s': not a valid identifier\n", command[i]);
		}
		i++;
	}
	free_tab(command);
}
