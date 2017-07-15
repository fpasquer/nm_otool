/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:41:54 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/15 12:51:55 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

static bool					save_output(t_nm const **nm, struct symtab_command
		const *sym)
{
	char					*stringtable;
	uint32_t				i;
	struct nlist_64			*array;

	if (nm == NULL || *nm == NULL || sym == NULL)
		ERROR_EXIT("Invalid arguments 2", __FILE__, NULL, NULL);
	//printf("nb symbole : %d\n", sym->nsyms);									//allouer un tableau de struct de la taille de sym->nsyms
	i = 0;
	array = (void*)(*nm)->data + sym->symoff;
	stringtable = (void*)(*nm)->data + sym->stroff;
	while(i < sym->nsyms)
	{
		printf("%llx %02x %s\n", array[i].n_value, array[i].n_type, stringtable + array[i].n_un.n_strx);
		i++;
	}
	return (true);
}

static bool					loop_func_64(t_nm const **nm,
		struct mach_header_64 const *header, struct load_command *lc)// changer header par la valeur de ncmds
{
	uint32_t				i;

	if (nm == NULL || *nm == NULL || header == NULL || lc == NULL)
		ERROR_EXIT("Invalid arguments", __FILE__, NULL, NULL);
	i = 0;
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			return (save_output(nm, (struct symtab_command const *)lc));
		if ((void*)(lc = (void *)lc + lc->cmdsize) > (void*)(*nm)->end)
			ERROR_EXIT("Ptr lc over the end 2", __FILE__, del_nm, nm);
	}
	return (false);
}

bool						func_64(t_nm const **nm)
{
	struct mach_header_64	*header;
	struct load_command		*lc;

	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
	header = (struct mach_header_64*)(*nm)->data;
	if((void*)(lc = (void*)(*nm)->data + sizeof(*header)) >
			(void*)(*nm)->end)
		ERROR_EXIT("Ptr lc over the end", __FILE__, del_nm, nm);
																				//printf("Magic number for 64 bits = 0x%x %x\n", header->magic, header->cputype);
	return (loop_func_64(nm, header, lc));
}