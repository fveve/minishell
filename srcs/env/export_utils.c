/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:27:34 by leoherna          #+#    #+#             */
/*   Updated: 2024/02/26 17:27:34 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alpha_reorder4(int *j, int *k, char *ascii_char, char **env)
{
	(*j)++;
	if (*k != ft_strlen2(env) && *j == ft_strlen2(env))
	{
		*j = 0;
		(*ascii_char)++;
	}
}

void	alpha_reorder3(int *j, int *k, char *ascii_char, char **env)
{
	if (*j == ft_strlen2(env))
	{
		(*ascii_char)++;
		*j = 0;
	}
	(*k)++;
}

char	*alpha_reorder2(char **env, int *i, int *j)
{
	char	*new_env;

	new_env = NULL;
	new_env = malloc (sizeof(char) * (ft_strlen(env[*j]) + 1));
	while (env[*j][*i] != '\0')
	{
		new_env[*i] = env[*j][*i];
		(*i)++;
	}
	new_env[*i] = '\0';
	*i = 0;
	return (new_env);
}

char	**alpha_reorder(char **env)
{
	char	ascii_char;
	int		k;
	int		j;
	int		i;
	char	**new_env;

	j = 0;
	k = 0;
	i = 0;
	ascii_char = 32;
	new_env = malloc(sizeof(char *) * (ft_strlen2(env) + 1));
	while (ft_strlen2(env) != k)
	{
		if (env[j][0] == ascii_char)
		{
			new_env[k] = alpha_reorder2(env, &i, &j);
			alpha_reorder3(&j, &k, &ascii_char, env);
		}
		alpha_reorder4(&j, &k, &ascii_char, env);
	}
	new_env[k] = NULL;
	return (new_env);
}

char	**return_new_export_env(t_mini *mini, char *new_env_var)
{
	char	*env_one_line;
	char	*temp;
	int		i;

	i = 1;
	env_one_line = ft_strjoin(mini->export_env[0], " ");
	while (i != ft_strlen2(mini->export_env))
	{
		temp = ft_strjoin(env_one_line, " ");
		free(env_one_line);
		env_one_line = ft_strjoin(temp, mini->export_env[i]);
		free(temp);
		i++;
	}
	temp = ft_strjoin(env_one_line, " ");
	free(env_one_line);
	env_one_line = ft_strjoin(temp, new_env_var);
	free(temp);
	return (free_export_unset(env_one_line));
}
