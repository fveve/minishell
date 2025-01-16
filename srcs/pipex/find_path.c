/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:46:09 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 13:50:07 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_space(char **cmd);

char	**find_path2(char **env);

int	is_path(char *s)
{
	int		x;

	x = 0;
	while (s[x] && ft_strncmp(s, "PATH", 4) != 0)
	{
		x++;
	}
	if (ft_strncmp(s, "PATH", 4) != 0)
		return (0);
	return (1);
}

void	verify_path(char *path)
{
	if (access(path, F_OK && X_OK) == -1)
		g_sig_error_code = 127;
}

char	*ft_set_path(char *cmd, char *p)
{
	char	*path;
	int		x;
	int		y;

	path = malloc(sizeof(char) * (ft_strlen(p) + ft_strlen(cmd) + 2));
	x = 0;
	y = 0;
	while (p[x])
		path[y++] = p[x++];
	path[y++] = '/';
	x = 0;
	while (cmd[x])
		path[y++] = cmd[x++];
	path[y] = '\0';
	return (path);
}

char	*find_path(char *cmd, char **env)
{
	char	**env2;
	char	*path;
	int		x;

	x = 0;
	env2 = find_path2(env);
	path = ft_set_path(cmd, env2[x]);
	while (access(path, F_OK && X_OK) == -1 && env2[x])
	{
		if (path)
			free(path);
		path = ft_set_path(cmd, env2[x]);
		x++;
	}
	free_tab(env2);
	verify_path(path);
	return (path);
}

int	is_file(char *s)
{
	if (!s)
		return (0);
	if (access(s, F_OK) == 0)
		return (1);
	return (0);
}
