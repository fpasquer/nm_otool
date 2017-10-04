/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:41:54 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/04 10:12:57 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

#define T	uint32_t i; struct nlist_64 *tab; t_symbol *ret;

static t_symbol				*save_output_64(t_nm **nm, struct symtab_command
		const *sym, void const *ptr)
{
	char					*str_table;

	T;
	if (nm == NULL || *nm == NULL || sym == NULL)
		ERROR_EXIT("Invalid arguments 2", __FILE__, NULL, NULL);
	if ((ret = (t_symbol *)ft_memalloc(sizeof(*ret) * sym->nsyms)) == NULL)
		return (NULL);
	i = 0;
	if ((void*)(tab = (void*)ptr + sym->symoff) + sizeof(*tab) * sym->nsyms
			> (void*)(*nm)->end)
		ERROR_EXIT("PTR OVERFLOW 3", __FILE__, NULL, NULL);
	str_table = (void*)ptr + sym->stroff;
	(*nm)->nb_symbol = sym->nsyms;
	while (i++ < sym->nsyms)
	{
		if ((void*)str_table + tab[i - 1].n_un.n_strx > (void*)(*nm)->end)
			ERROR_EXIT("PTR OVERFLOW 3", __FILE__, NULL, NULL);
		ret[i - 1].value = tab[i - 1].n_value;
		ret[i - 1].type = tab[i - 1].n_type;
		ret[i - 1].sect = tab[i - 1].n_sect;
		ret[i - 1].desc = tab[i - 1].n_desc;
		if (!(ret[i - 1].name = ft_strdup(str_table + tab[i - 1].n_un.n_strx)))
			break ;
	}
	return (ret);
}

static char					*get_symbol_64_2(
		struct segment_command_64 *seg_cmd, struct section_64 *sec,
		t_symbol const symbol, uint8_t *j)
{
	uint32_t				i;

	i = 0;
	if (seg_cmd->nsects <= 0)
		return ("");
	while (i++ < seg_cmd->nsects)
	{
		if (++(*j) == symbol.sect)
		{
			if (ft_strcmp(sec->sectname, SECT_DATA) == 0)
				return ((symbol.type & N_EXT) == 0 ? "d" : "D");
			else if (ft_strcmp(sec->sectname, SECT_BSS) == 0)
				return ((symbol.type & N_EXT) == 0 ? "b" : "B");
			else if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
				return ((symbol.type & N_EXT) == 0 ? "t" : "T");
			return ((symbol.type & N_EXT) == 0 ? "s" : "S");
		}
		sec = (struct section_64 *)((char *)sec + sizeof(struct section_64));
	}
	return ("");
}

static t_symbol				*loop_func_64(t_nm **nm,
		struct mach_header_64 const *header, struct load_command *lc,
		void const *ptr)
{
	uint32_t				i;

	if (nm == NULL || *nm == NULL || header == NULL || lc == NULL)
		ERROR_EXIT("Invalid arguments", __FILE__, NULL, NULL);
	i = 0;
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			return (save_output_64(nm, (struct symtab_command const *)lc, ptr));
		if ((void*)(lc = (void *)lc + lc->cmdsize) > (void*)(*nm)->end)
			ERROR_EXIT("Ptr lc over the end 2", __FILE__, del_nm, nm);
	}
	return (NULL);
}

t_symbol					*func_64(t_nm **nm, void *ptr, char const *name_bin)
{
	struct mach_header_64	*header;
	struct load_command		*lc;

	if (nm == NULL || *nm == NULL || ptr == NULL || name_bin == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
	if ((size_t)(*nm)->buff.st_size <= sizeof(struct mach_header_64))
		return (NULL);
	(*nm)->len_addr = LEN_64_BIT;
	header = (struct mach_header_64*)ptr;
	(*nm)->magic = header->magic;
	if ((void*)(lc = (void*)ptr + sizeof(*header)) + sizeof(*lc) >
			(void*)(*nm)->end)
		ERROR_EXIT("Ptr lc over the end", __FILE__, del_nm, nm);
	return (loop_func_64(nm, header, lc, ptr));
}

char						*get_symbol_64(t_symbol const symbol,
		void const *ptr)
{
	char					*ret;
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	uint8_t					j;

	header = (struct mach_header_64*)ptr;
	lc = (void*)ptr + sizeof(*header);
	i = 0;
	j = 0;
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			ret = get_symbol_64_2((void *)lc, (void *)lc + sizeof(
					struct segment_command_64), symbol, &j);
			if (ft_strlen(ret) > 0)
				return (ret);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return ("ERROR");
}
