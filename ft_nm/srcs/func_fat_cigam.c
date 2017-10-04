/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_fat_cigam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 17:49:18 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/04 10:01:50 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

uint32_t					b_to_l_endian(uint32_t num)
{
	return (((num >> 24) & 0xff) |
			((num << 8) & 0xff0000) |
			((num >> 8) & 0xff00) |
			((num << 24) & 0xff000000));
}

static t_symbol				*loop_fat(t_nm **nm, const uint32_t end, void *ptr,
		char const *name_bin)
{
	uint32_t				i;
	uint32_t				offset_arch;
	t_symbol				*symbol;
	struct fat_arch			*arch;

	if (nm == NULL || *nm == NULL || ptr == NULL || name_bin == NULL)
		ERROR_EXIT("NM = NULL 2", __FILE__, NULL, NULL);
	i = 0;
	if ((void*)(arch = (void*)ptr + sizeof(struct fat_header*)) >
			(void*)(*nm)->end)
		ERROR_EXIT("Ptr arch over the end", __FILE__, del_nm, nm);
	while (i++ < end)
	{
		if (b_to_l_endian(arch->cputype) == CPU_TYPE &&
			b_to_l_endian(arch->cpusubtype & CPU_SUBTYPE_MASK) == CPU_SUB_TYPE)
		{
			offset_arch = b_to_l_endian(arch->offset);
			if ((symbol = exe_nm(nm, name_bin, ptr + offset_arch)) != NULL)
				gestion_symbols(nm, &symbol, name_bin, ptr + offset_arch);
			reset_struct_nm(nm, ptr + offset_arch);
		}
		if ((void*)(arch = (void*)arch + sizeof(*arch)) > (void*)(*nm)->end)
			ERROR_EXIT("Ptr arch over the end 2", __FILE__, del_nm, nm);
	}
	return (NULL);
}

t_symbol					*func_fat_cigam(t_nm **nm, void *ptr,
		char const *name_bin)
{
	struct fat_header		*header;

	if (nm == NULL || *nm == NULL || ptr == NULL || name_bin == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
	if ((size_t)(*nm)->buff.st_size <= sizeof(struct fat_header))
		return (NULL);
	(*nm)->fat = true;
	header = (struct fat_header*)ptr;
	return (loop_fat(nm, b_to_l_endian(header->nfat_arch), ptr, name_bin));
}
