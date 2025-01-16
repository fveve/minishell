/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:44:12 by leoherna          #+#    #+#             */
/*   Updated: 2024/06/12 12:33:08 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp2(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		if (i < (size - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

void	ft_putstr_fd(int fd, char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		write(fd, &str[x], 1);
		x++;
	}
	write(fd, "\n", 1);
}

char	**replace_buffer(char **buffer, char *line)
{
	char	**input_lines;
	int		x;

	x = 0;
	if (buffer)
	{
		input_lines = malloc(sizeof(char *) * (ft_strlen2(buffer) + 2));
		while (buffer[x])
		{
			input_lines[x] = ft_strdup(buffer[x]);
			x++;
		}
		free_tab(buffer);
	}
	else
		input_lines = malloc(sizeof(char *) * 2);
	input_lines[x] = ft_strdup(line);
	x++;
	input_lines[x] = NULL;
	return (input_lines);
}

void	handle_here_doc2(t_data *data, char **buffer)
{
	int	x;

	x = 0;
	if (pipe(data->fd[data->index]) == -1)
	{
		free_tab(buffer);
		perror("Pipe");
		return ;
	}
	if (buffer)
	{
		while (buffer[x])
		{
			ft_putstr_fd(data->fd[data->index][1], buffer[x]);
			x++;
		}
	}
	free_tab(buffer);
	close(data->fd[0][1]);
	data->index++;
}

void	handle_here_doc(t_data *data, char *word)
{
	char		*input_str;
	char		**buffer;

	dup2(data->_stdin, 0);
	input_str = readline("\001\033[38;5;197m\002> \001\033[0m\002");
	buffer = NULL;
	if (input_str && ft_strncmp2(word, input_str, 100000))
		buffer = replace_buffer(buffer, input_str);
	while (input_str && ft_strncmp2(word, input_str, 100000))
	{
		if (input_str)
			free(input_str);
		input_str = readline("\001\033[38;5;197m\002> \001\033[0m\002");
		if (!input_str
			|| !ft_strncmp2(word, input_str, 100000))
			break ;
		else
			buffer = replace_buffer(buffer, input_str);
		if (!ft_strncmp2(word, input_str, 100000))
			rl_on_new_line();
	}
	free(input_str);
	handle_here_doc2(data, buffer);
	free(word);
}
