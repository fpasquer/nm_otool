/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 11:45:09 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/24 11:49:55 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

void						*func_32(t_otool *otool, char const *name,
		void const *ptr)
{
	if (otool == NULL || name == NULL || ptr == NULL || ptr > otool->end)
		return (NULL);
	otool->cigam = (*(uint32_t *)ptr == MH_CIGAM) ? true : false;
																				printf("32bits\n");
	return (NULL);
}