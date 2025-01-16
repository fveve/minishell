/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:01:08 by leoherna          #+#    #+#             */
/*   Updated: 2023/10/03 14:40:35 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static int	count_size(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		count++;
	}
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	if (count == 0)
		count++;
	return (count);
}

static char	*transformer(int count, long nbr, char *tab)
{
	int	sign;

	sign = 0;
	if (nbr < 0)
	{
		sign++;
		nbr = nbr * -1;
		tab[0] = '-';
	}
	while (count > sign)
	{
		count--;
		tab[count] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (tab);
}

char	*ft_itoa(int nb)
{
	int		count;
	char	*tab;
	long	nbr;

	nbr = nb;
	count = count_size(nbr);
	tab = malloc(sizeof(char) * count + 1);
	if (!tab)
		return (NULL);
	tab[count] = '\0';
	return (transformer(count, nbr, tab));
}
