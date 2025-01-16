/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_enhanced.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:58:33 by marvin            #+#    #+#             */
/*   Updated: 2024/06/13 19:58:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_char(const char *s1, const char c)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_cote(int *val, char c)
{
	if (*val == c && *val > 0)
		*val = 0;
	else if (*val == 0 && (c == '"' || c == '\''))
		*val = c;
}

int	ft_countwords(char const *s, char *c, int *trig_cote)
{
	int	i;
	int	count;
	int	trig;

	i = 0;
	count = 0;
	trig = 0;
	*trig_cote = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		ft_cote(trig_cote, s[i]);
		if (trig == 0 && ft_find_char(c, s[i]) == 0)
		{
			count++;
			trig = 1;
		}
		else if (ft_find_char(c, s[i]) == 1 && *trig_cote == 0)
			trig = 0;
		i++;
	}
	*trig_cote = 0;
	return (count);
}

static char	*ft_splitword(char const *s, int *index, int i, int bol_quote)
{
	char	*str;
	int		trig;
	int		old_trig;
	int		j;

	trig = 0;
	str = malloc((i - *index + 1) * sizeof(char));
	j = 0;
	while (*index < i)
	{
		old_trig = trig;
		ft_cote(&trig, s[*index]);
		if ((s[*index] != '"' && s[*index] != '\'') || trig == old_trig
			|| bol_quote == 1)
			str[j++] = s[*index];
		++*index;
	}
	str[j++] = '\0';
	*index = -1;
	return (str);
}

char	**ft_split(char *s, char *c, int bol_quote)
{
	char	**tab;
	int		i;
	int		j;
	int		index;
	int		trig_cote;

	if (s == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_countwords(s, c, &trig_cote) + 1));
	if (!tab)
		return (NULL);
	i = -1;
	j = 0;
	index = -1;
	while (++i <= ft_strlen(s))
	{
		ft_cote(&trig_cote, s[i]);
		if (ft_find_char(c, s[i]) == 0 && index == -1)
			index = i;
		else if (((ft_find_char(c, s[i]) == 1 && trig_cote == 0)
				|| i == ft_strlen(s)) && index != -1)
			tab[j++] = ft_splitword(s, &index, i, bol_quote);
	}
	tab[j] = NULL;
	return (tab);
}
/*int	main (void)
{
	char	**temp = ft_split("echo   \' dsdds", " \'\"");
	it_works(temp);
	free_tab(temp);
}*/
