/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:58:58 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 14:54:28 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		n_o_r(char *input_str);

int		n_i_r(char *input_str);

void	go_to_file(char *input_str, int *y, int *x);

void	set_file(t_data *data, char *file, char *input_str, int trigger);

int		is_double(char	*input);

void	ft_open_file(char *input, int x)
{
	char	*file;
	int		z;
	int		y;
	int		fd;

	z = x;
	y = x;
	go_to_file(input, &y, &z);
	file = ft_substr(input, z, y - z);
	fd = open(file, O_CREAT);
	close(fd);
	free(file);
}

void	set_fd2(t_data *data, char *input_str, int *x, int *z)
{
	char	*file;
	int		y;

	y = 0;
	*z = n_o_r(input_str);
	if (*z > 1)
	{
		while (input_str[*x] && *z > 0)
		{
			if (input_str[*x] == '>' && input_str[*x - 1] != '>')
			{
				if (*z > 1)
					ft_open_file(input_str, *x);
				(*z)--;
			}
			(*x)++;
		}
	}
	go_to_file(input_str, &y, x);
	file = ft_substr(input_str, *x, y - *x);
	if (!is_double(input_str))
		set_file(data, file, input_str, 2);
	else
		set_file(data, file, input_str, 3);
	free(file);
}

void	set_fd3(t_data *data, char *input_str, int *x, int trigger)
{
	char	*file;
	int		y;

	file = NULL;
	y = 0;
	go_to_file(input_str, &y, x);
	file = ft_substr(input_str, *x, y - *x);
	if (!is_double(input_str))
		set_file(data, file, input_str, 0);
	else if (trigger)
		set_file(data, file, input_str, 1);
	free(file);
}

void	set_fd4(t_data *data, char *input_str, int *x, int *z)
{
	*z = n_i_r(input_str);
	while (input_str[*x] && *z > 0)
	{
		if (input_str[*x] == '<' && input_str[*x - 1] != '<')
			(*z)--;
		else if (input_str[*x] == '<' && input_str[*x - 1] == '<')
			set_fd3(data, input_str, x, 1);
		(*x)++;
	}
}

void	set_fd(t_data *data, char *input_str)
{
	int	x;
	int	z;

	x = 0;
	z = 0;
	if (data->cmd.trigger == 1)
	{
		while (x < ft_strlen(input_str))
		{
			if (input_str[x] == '<' && input_str[x + 1] != '<'
				&& !is_in_quote(input_str, "<", x))
			{
				set_fd4(data, input_str, &x, &z);
				set_fd3(data, input_str, &x, 0);
			}
			else if (input_str[x] == '>' && !is_in_quote(input_str, "<", x))
				set_fd2(data, input_str, &x, &z);
			x++;
		}
	}
}
