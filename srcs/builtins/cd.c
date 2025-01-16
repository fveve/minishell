/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:31:37 by leoherna          #+#    #+#             */
/*   Updated: 2024/02/22 19:31:37 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_export_env(t_mini *mini)
{
	int		i;
	char	current_dir[1024];

	i = 0;
	getcwd(current_dir, 1024);
	while (mini->export_env[i]
		&& ft_strncmp(mini->export_env[i], "OLDPWD", 6) != 0)
		i++;
	free(mini->export_env[i]);
	mini->export_env[i] = ft_strjoin("OLDPWD=", current_dir);
}

void	update_env(t_mini *mini)
{
	int		i;
	char	current_dir[1024];

	i = 0;
	getcwd(current_dir, 1024);
	while (mini->env[i] && ft_strncmp(mini->env[i], "OLDPWD", 6) != 0)
		i++;
	free(mini->env[i]);
	mini->env[i] = ft_strjoin("OLDPWD=", current_dir);
	update_export_env(mini);
}

int	cd_cmd3(t_mini *mini, char **command, char **path, char *temp)
{
	temp = get_env_path(mini, 1);
	if (temp == NULL)
	{
		printf("-bash: cd: OLDPWD not set\n");
		g_sig_error_code = 1;
		free_tab(command);
		return (0);
	}
	*path = ft_strdup(temp);
	ft_putstr_fd(1, *path);
	free(temp);
	return (1);
}

int	cd_cmd2(t_mini *mini, char **command, char *path, char *temp)
{
	if (ft_strncmp(command[1], "-", 1) == 0)
	{
		if (!cd_cmd3(mini, command, &path, temp))
			return (0);
	}
	else if (ft_strncmp(command[1], "~", 1) == 0)
	{
		if (cd_wave(mini, command, path) == 0)
			return (free_tab(command), 0);
		return (1);
	}
	else
		path = ft_strdup(command[1]);
	update_env(mini);
	if (chdir(path) != 0)
	{
		g_sig_error_code = 1;
		printf("Erreur lors du changement de répertoire\n");
	}
	if (path)
		free(path);
	return (1);
}

int	cd_cmd(t_mini *mini, char *cmd)
{
	char	**command;
	char	*path;
	char	*temp;

	path = NULL;
	temp = NULL;
	command = NULL;
	command = ft_split(cmd, " ", 0);
	if (ft_strlen2(command) == 1)
	{
		if (cd_alone(mini, path) == 0)
		{
			free_tab(command);
			return (0);
		}
	}
	else if (!cd_cmd2(mini, command, path, temp))
		return (0);
	if (path)
		free(path);
	free_tab(command);
	return (update_env2(mini), 1);
}
