/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strsplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:49:56 by fpasquer          #+#    #+#             */
/*   Updated: 2017/05/24 08:58:51 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_free_strsplit(char **tab)
{
	unsigned int	y;

	y = 0;
	while (tab[y] != NULL)
	{
		free(tab[y]);
		tab[y++] = NULL;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}
