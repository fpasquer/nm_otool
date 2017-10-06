/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_fat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 11:50:46 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/06 12:15:26 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"
#define INIT otool->fat = true; otool->end_seg = end; i = 0;

static void					*func_fat2(t_otool *otool, char const *name,
	void const *ptr)
{
	uint32_t				i;
	uint32_t				end;
	struct fat_header		*head;
	struct fat_arch			*arch;

	if (otool == NULL || name == NULL || ptr == NULL || ptr > otool->end)
		return (NULL);
	if (((void*)(head = (struct fat_header *)ptr)) + sizeof(*head) >=
			(void*)otool->end)
		return ((void*)put_error_file("Over the end aghsjd hsak "));
	if (((void*)(arch = (void *)ptr + sizeof(*head))) + sizeof(*arch) * 2 >=
			(void*)otool->end)
		return ((void*)put_error_file("Over the end aghsjasdasdsad hsak "));
	otool->cigam = (head->magic == FAT_CIGAM) ? true : false;
	end = otool->cigam ? b_to_l_endian(head->nfat_arch) : head->nfat_arch;
	i = 0;
	otool->not_foond = true;
	while (i++ < end)
	{
		otool->cpu_type = B_TO_L(otool->cigam, arch->cputype);
		if ((void*)(ptr + B_TO_L(otool->cigam, arch->offset)) < otool->end)
			exe_otool(otool, name, ptr + (B_TO_L(otool->cigam, arch->offset)));
		arch = (void*)arch + sizeof(*arch);
	}
	return (NULL);
}

void						*func_fat(t_otool *otool, char const *name,
		void const *ptr)
{
	uint32_t				i;
	uint32_t				end;
	struct fat_header		*head;
	struct fat_arch			*arch;

	if (otool == NULL || name == NULL || ptr == NULL || ptr > otool->end)
		return (NULL);
	if (((void*)(head = (struct fat_header *)ptr)) + sizeof(*head) >=
			(void*)otool->end)
		return ((void*)put_error_file("Over the end aghsjd hsak "));
	if (((void*)(arch = (void *)ptr + sizeof(*head))) + sizeof(*arch) * 2 >=
			(void*)otool->end)
		return ((void*)put_error_file("Over the end aghsjasdasdsad hsak "));
	otool->cigam = (head->magic == FAT_CIGAM) ? true : false;
	end = otool->cigam ? b_to_l_endian(head->nfat_arch) : head->nfat_arch;
	INIT;
	while (i++ < end)
	{
		if (CPU_TYPE == (B_TO_L(otool->cigam, arch->cputype)))
			if ((void*)(ptr + B_TO_L(otool->cigam, arch->offset)) < otool->end)
				return (exe_otool(otool, name, ptr + (B_TO_L(otool->cigam,
						arch->offset))));
				arch = (void*)arch + sizeof(*arch);
	}
	return (func_fat2(otool, name, ptr));
}
