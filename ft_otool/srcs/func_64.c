/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 11:50:05 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/24 11:50:36 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

void						*func_64(t_otool *otool, char const *name,
		void const *ptr)
{
	if (otool == NULL || name == NULL || ptr == NULL || ptr > otool->end)
		return (NULL);
	otool->cigam = (*(uint32_t *)ptr == MH_CIGAM_64) ? true : false;
																				printf("64bits\n");
	return (NULL);
}