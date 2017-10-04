/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:59:28 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/04 13:41:05 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#define MAX_BASE 16

char						*ft_utoa_base(unsigned long long int nb,
		const unsigned int base)
{
	char						*ret;
	static unsigned int			loop;
	static unsigned int			i;
	unsigned long long int		mem;

	if (base < 2 || base > 36)
		return (NULL);
	if (nb == 0)
	{
		if ((ret = ft_memalloc(sizeof(char) * (loop > 0 ? loop + 1 : 2))) ==
				NULL)
			return (NULL);
		if (loop == 0)
			ret[0] = '0';
		loop = 0;
		i = 0;
		return (ret);
	}
	loop++;
	mem = nb % base;
	ret = ft_utoa_base(nb / base, base);
	ret[i++] = (mem < 10) ? (char)mem + '0' : (char)mem - 10 + 'a';
	return (ret);
}

bool						ft_utoa_base_tab(unsigned long long int nb,
		unsigned int base, char *tab, size_t max)
{
	size_t					i;
	static char				c_base[MAX_BASE] = {'0', '1', '2', '3', '4', '5',
			'6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	unsigned long long int	nb_mem;

	if (max <= 0 || tab == NULL || base < 2 || base > MAX_BASE)
		return (false);
	i = 0;
	nb_mem = nb;
	while (nb_mem > 0 && i++ < max)
		nb_mem /= base;
	if (i > max)
		return (false);
	if (nb == 0)
		tab[i] = '0';
	else
		while (nb > 0)
		{
			tab[--i] = c_base[nb % base];
			nb /= base;
		}
	return (true);
}
