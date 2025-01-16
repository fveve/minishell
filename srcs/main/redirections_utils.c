/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:14:55 by arafa             #+#    #+#             */
/*   Updated: 2024/06/12 12:37:58 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_printable(char c)
{
	if (c >= 32 && c <= 126 && c != '<' && c != '>' && c != ' ')
		return (1);
	return (0);
}

void	verify_path2(char *path)
{
	if (access(path, F_OK && X_OK) == -1)
	{
		printf("Error : no such file or directory");
		free(path);
	}
}

void	go_to_file(char *input_str, int *y, int *x)
{
	*y = *x;
	while (input_str[*y] && !is_printable(input_str[*y]))
	{
		(*x)++;
		(*y)++;
	}
	while (input_str[*y] && is_printable(input_str[*y]))
		(*y)++;
}

char	*get_word(t_data *data, char *input_str)
{
	char	*word;
	int		x;
	int		y;
	int		index;

	x = 0;
	y = 0;
	index = data->index;
	while (index >= 0)
	{
		while (input_str[x] && input_str[x] != '<')
			x++;
		x++;
		x++;
		index--;
	}
	while (input_str[x] && !is_printable(input_str[x]))
		x++;
	y = x;
	while (input_str[y] && is_printable(input_str[y]))
		y++;
	word = ft_substr(input_str, x, y - x);
	return (word);
}

void	set_file(t_data *data, char *file, char *input_str, int trigger)
{
	char	*word;

	word = NULL;
	if (!trigger)
		data->fd[data->index][0] = open(file, O_RDONLY);
	else if (trigger == 1)
	{
		word = get_word(data, input_str);
		handle_here_doc(data, word);
	}
	if (trigger == 2)
		data->fd[data->index][1] = open(file, O_WRONLY
				| O_CREAT | O_TRUNC, 0600);
	else if (trigger == 3)
		data->fd[data->index][1] = open(file, O_WRONLY | O_APPEND | O_CREAT);
	data->index++;
}
