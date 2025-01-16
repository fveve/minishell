/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:35:03 by leoherna          #+#    #+#             */
/*   Updated: 2024/04/05 09:35:03 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_redirection(char *input_str);

void	go_to_file(char *input_str, int *y, int *x);

int		verify_redirection(char *input);

int		verify_redirection2(char *input);

int		verify_redirection4(char *input);

int		verify_cmd2(char	*input, int x);

int		verify_cmd3(char	*input);

int		verify_quote2(char *input, int *x);

int		verify_pipe(char *input);

int	verify_quote(char	*input)
{
	int	x;

	x = 0;
	while (input[x])
	{
		if (input[x] == '\'')
		{
			if (verify_quote2(input, &x))
				return (1);
		}
		else if (input[x] == '\"')
		{
			x++;
			while (input[x] && input[x] != '\"')
				x++;
			if (!input[x] || input[x] != '\"')
			{
				printf("Quote need to be closed\n");
				return (1);
			}
		}
		x++;
	}
	return (0);
}

int	is_quote(const char *input)
{
	int	x;

	x = 0;
	while (input[x])
	{
		if (input[x] == '\'' || input[x] == '\"')
			return (1);
		x++;
	}
	return (0);
}

int	is_space(char *input)
{
	int	x;

	x = 0;
	while (input[x])
	{
		if (input[x] == ' ')
			return (1);
		x++;
	}
	return (0);
}

int	verify_cmd(char	*input, int x)
{
	if (ft_countwords(input, " ", &x) > 1 || is_space(input))
	{
		if (verify_cmd2(input, 1))
			return (1);
	}
	else
	{
		if (verify_cmd3(input))
			return (1);
		if (ft_strncmp(input, "export", ft_strlen(input)) == 0
			&& ft_strlen(input) != ft_strlen("export"))
			return (1);
		if (ft_strncmp(input, "unset", ft_strlen(input)) == 0
			&& ft_strlen(input) != ft_strlen("unset"))
			return (1);
		if (ft_strncmp(input, "exit", ft_strlen(input)) == 0
			&& ft_strlen(input) != ft_strlen("exit"))
			return (1);
		if (ft_strncmp(input, "echo", ft_strlen(input)) == 0
			&& ft_strlen(input) != ft_strlen("echo"))
			return (1);
	}
	return (0);
}

int	analyse_input(char *input)
{
	if (is_redirection(input))
		if (verify_redirection(input) || verify_redirection2(input)
			|| verify_redirection4(input))
			return (1);
	if (is_quote(input))
		if (verify_quote(input))
			return (1);
	if (verify_cmd(input, 1))
	{
		printf("Error : no such file or directory\n");
		return (1);
	}
	if (verify_pipe(input))
	{
		printf("Error : wrong input\n");
		return (1);
	}
	return (0);
}
