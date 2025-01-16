/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:40:38 by leoherna          #+#    #+#             */
/*   Updated: 2024/06/14 14:45:19 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tiret_n(char *str, int *option_n)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (1);
	if (ft_strlen(str) >= 2)
	{
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
	}
	*option_n = 1;
	return (0);
}

void	it_works(char **tab)
{
	int	j;

	j = 0;
	if (!tab || !tab[j])
	{
		printf("nb lines : 0\n");
		printf("(null)\n");
		return ;
	}
	while (tab[j] != NULL)
	{
		if (tab[j])
			printf("%s\n", tab[j]);
		j++;
	}
}

char	*ft_strdup(char *src)
{
	int		i;
	int		size;
	char	*copy;

	i = 0;
	size = ft_strlen(src) + 1;
	copy = malloc (size * sizeof(char));
	if (!copy)
		return (0);
	while (src[i] != '\0')
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	ft_strlen_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strdup_equal(char *src)
{
	int		i;
	int		size;
	char	*copy;

	i = 0;
	size = ft_strlen_equal(src) + 1;
	copy = malloc (size * sizeof(char));
	if (!copy)
		return (0);
	while (src[i] != '\0')
	{
		if (src[i] == '=')
		{
			copy[i] = '\0';
			return (copy);
		}
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
