/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:16:51 by leoherna          #+#    #+#             */
/*   Updated: 2024/06/11 14:50:05 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipes(t_cmd *cmd, char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		skip_comma(str, &x);
		if (str[x] == '|')
			cmd->pipes++;
		x++;
	}
	if (cmd->pipes >= 0)
	{
		cmd->pipes++;
		cmd->is_pipe = 1;
		return (1);
	}
	return (0);
}

int	is_command(char *str, int x)
{
	char	*word;
	int		end;

	end = x;
	while (str[end] && str[end] != ' ')
		end++;
	word = malloc(sizeof(char) * ((end - x) + 2));
	word[(end - x) + 1] = '\0';
	end = 0;
	while (str[x] && str[end] != ' ')
		word[end++] = str[x++];
	if (ft_strncmp(word, "pwd", ft_strlen(word)) == 0
		|| ft_strncmp(word, "cd", ft_strlen(word)) == 0
		|| ft_strncmp(word, "env", ft_strlen(word)) == 0
		|| ft_strncmp(word, "export", ft_strlen(word)) == 0
		|| ft_strncmp(word, "unset", ft_strlen(word)) == 0
		|| ft_strncmp(word, "exit", ft_strlen(word)) == 0
		|| ft_strncmp(word, "echo", ft_strlen(word)) == 0)
	{
		free(word);
		return (1);
	}
	free(word);
	return (0);
}

int	just_space(char	*str, int y)
{
	if (str && y < ft_strlen(str))
	{
		while (str[y])
		{
			if (str[y] != ' ')
				return (0);
			y++;
		}
	}
	return (1);
}

char	*remove_space2(char **cmd, char *temp, int x, int y)
{
	int	z;

	z = 0;
	while (cmd[x][y] == ' ')
		y++;
	temp = malloc(sizeof(char) * (ft_strlen(cmd[x]) - y + 1));
	while (cmd[x][y] && !just_space(cmd[x], y))
	{
		temp[z] = cmd[x][y];
		z++;
		y++;
	}
	temp[z] = '\0';
	return (temp);
}

char	**remove_space(char **cmd)
{
	char	*temp;
	int		x;
	int		y;

	x = 0;
	y = 0;
	temp = NULL;
	if (cmd)
	{
		while (cmd[x] && ft_strlen(cmd[x]) > 1 && !just_space(cmd[x], y))
		{
			y = 0;
			temp = remove_space2(cmd, temp, x, y);
			free(cmd[x]);
			cmd[x] = ft_strdup(temp);
			free(temp);
			x++;
		}
	}
	return (cmd);
}
