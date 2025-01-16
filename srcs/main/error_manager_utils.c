/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:54:24 by arafa             #+#    #+#             */
/*   Updated: 2024/06/11 15:10:52 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_to_file(char *input_str, int *y, int *x);

int		verify_cmd(char	*input);

int		verify_cmd2(char *input, int x);

void	go_to_file3(char *input_str, int *x, int *y);

int		verify_redirection4(char *input);

int	verify_cmd3(char	*input)
{
	if (ft_strncmp(input, "pwd", ft_strlen(input)) == 0
		&& ft_strlen(input) != ft_strlen("pwd"))
		return (1);
	if (ft_strncmp(input, "cd", ft_strlen(input)) == 0
		&& ft_strlen(input) != ft_strlen("cd"))
		return (1);
	if (ft_strncmp(input, "env", ft_strlen(input)) == 0
		&& ft_strlen(input) != ft_strlen("env"))
		return (1);
	return (0);
}

int	verify_redirection3(char *file1)
{
	char	**temp;

	if (n_i_r(file1))
	{
		temp = malloc(sizeof(char *) * 2);
		temp[0] = ft_strdup(file1);
		temp[1] = NULL;
		remove_space(temp);
		if (access(temp[0], F_OK | O_RDONLY) < 0)
		{
			g_sig_error_code = 1;
			free_tab(temp);
			free(file1);
			return (1);
		}
		free_tab(temp);
		free(file1);
	}
	return (0);
}

void	go_to_file2(char *input_str, int *x, int *y)
{
	int	trigger;

	trigger = -1;
	while (input_str[*x])
	{
		if (input_str[*x] == '<')
			trigger++;
		(*x)++;
	}
	*x = 0;
	while (input_str[*x])
	{
		if (input_str[*x] == '<' && trigger)
			trigger--;
		else if (input_str[*x] == '<' && !trigger)
		{
			go_to_file(input_str, y, x);
			return ;
		}
		(*x)++;
	}
}

int	verify_redirection2(char *input)
{
	char	*file;
	int		x;
	int		y;

	x = 0;
	y = 0;
	go_to_file2(input, &x, &y);
	file = ft_substr(input, x, y - x);
	if (!file)
	{
		x = 0;
		y = 0;
		go_to_file3(input, &x, &y);
		file = ft_substr(input, x, y - x);
	}
	if (!file)
	{
		g_sig_error_code = 1;
		printf("Error : no input file\n");
		free(file);
		return (1);
	}
	free(file);
	return (0);
}

int	verify_redirection(char *input)
{
	char	*file1;
	int		x;
	int		y;

	x = 0;
	y = 0;
	go_to_file2(input, &x, &y);
	file1 = ft_substr(input, x, y - x);
	if (!file1)
	{
		x = 0;
		y = 0;
		go_to_file3(input, &x, &y);
		file1 = ft_substr(input, x, y - x);
	}
	if (just_space(input, x) || verify_redirection3(file1))
	{
		printf("Error : file problem\n");
		free(file1);
		return (1);
	}
	free(file1);
	return (0);
}
