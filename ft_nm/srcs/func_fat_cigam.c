/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_fat_cigam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 17:49:18 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/20 16:34:56 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

uint32_t					big_to_little_endian(uint32_t num)
{
	return (((num>>24) & 0xff) |
			((num<<8) & 0xff0000) |
			((num>>8) & 0xff00) |
			((num<<24) & 0xff000000));
}

static t_symbol				*loop_fat(t_nm **nm, struct fat_arch *arch,
		const uint32_t end, void *ptr)
{
	uint32_t				i;
	uint32_t				offset_arch;
	t_symbol				*symbol;

	i = 0;
	while (i++ < end)
	{
		if (big_to_little_endian(arch->cputype) == CPU_TYPE)
		{
			offset_arch = big_to_little_endian(arch->offset);
			if ((symbol = exe_nm(nm, "ADD NAME", ptr + offset_arch)) != NULL)
				gestion_symbols(nm, &symbol, "ADD NAME", ptr + offset_arch);
			reset_struct_nm(nm, ptr + offset_arch);
		}
		if ((void*)(arch = (void*)arch + sizeof(*arch)) > (void*)(*nm)->end)
			ERROR_EXIT("Ptr arch over the end 2", __FILE__, del_nm, nm);
	}
	return (NULL);
}

t_symbol					*func_fat_cigam(t_nm **nm, void *ptr)
{
	struct fat_header		*header;
	struct fat_arch			*arch;

	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
	header = (struct fat_header*)ptr;
	if((void*)(arch = (void*)ptr+ sizeof(*header)) > (void*)(*nm)->end)
		ERROR_EXIT("Ptr arch over the end", __FILE__, del_nm, nm);
	return (loop_fat(nm, arch, big_to_little_endian(header->nfat_arch), ptr));
	
}
