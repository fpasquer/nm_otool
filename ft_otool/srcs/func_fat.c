/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_fat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 11:50:46 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/24 11:51:07 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

void						*func_fat(t_otool *otool, char const *name,
		void const *ptr)
{
	if (otool == NULL || name == NULL || ptr == NULL || ptr > otool->end)
		return (NULL);
	otool->cigam = (*(uint32_t *)ptr == FAT_CIGAM) ? true : false;
																				printf("Fat bits\n");
	return (NULL);
}