/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:41:54 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/16 22:07:33 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

static t_symbol				*save_output(t_nm **nm, struct symtab_command
		const *sym)
{
	char					*stringtable;
	uint32_t				i;
	struct nlist_64			*array;
	t_symbol				*ret;

	if (nm == NULL || *nm == NULL || sym == NULL)
		ERROR_EXIT("Invalid arguments 2", __FILE__, NULL, NULL);
	if ((ret = (t_symbol *)ft_memalloc(sizeof(*ret) * sym->nsyms)) == NULL)
		return (NULL);
	i = 0;
	array = (void*)(*nm)->data + sym->symoff;
	stringtable = (void*)(*nm)->data + sym->stroff;
	(*nm)->nb_symbol = sym->nsyms;
	while(i < sym->nsyms)
	{
		ret[i].value = array[i].n_value;
		ret[i].type = array[i].n_type;
		ret[i].sect = array[i].n_sect;
		if ((ret[i].name = ft_strdup(stringtable + array[i].n_un.n_strx)) == NULL)
			break ;
		i++;
	}
	return (ret);
}

static t_symbol				*loop_func_64(t_nm **nm,
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
	return (NULL);
}

t_symbol					*func_64(t_nm **nm)
{
	struct mach_header_64	*header;
	struct load_command		*lc;

	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
	(*nm)->len_addr = LEN_64_BIT;
	header = (struct mach_header_64*)(*nm)->data;
	(*nm)->magic = header->magic;
	if((void*)(lc = (void*)(*nm)->data + sizeof(*header)) >
			(void*)(*nm)->end)
		ERROR_EXIT("Ptr lc over the end", __FILE__, del_nm, nm);
																				//printf("Magic number for 64 bits = 0x%x %x\n", header->magic, header->cputype);
	return (loop_func_64(nm, header, lc));
}