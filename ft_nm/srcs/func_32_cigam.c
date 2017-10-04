/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_32_cigam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:40:59 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/04 17:58:46 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

static t_symbol				*save_output_32_cigam(t_nm **nm, struct symtab_command
		*sym, void const *ptr)
{
	char					*str_table;
	uint32_t				i;
	struct nlist			*tab;
	t_symbol				*ret;

	if (nm == NULL || *nm == NULL || sym == NULL)
		ERROR_EXIT("Invalid arguments 2", __FILE__, NULL, NULL);
	swap_symtab_command(sym, NX_UnknownByteOrder);
	if ((ret = (t_symbol *)ft_memalloc(sizeof(*ret) * sym->nsyms)) == NULL)
		return (NULL);
	i = 0;
	swap_nlist(tab = (void*)ptr + sym->symoff, sym->nsyms, NX_UnknownByteOrder);
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
	swap_symtab_command(sym, NX_UnknownByteOrder);
	return (ret);
}

static t_symbol				*loop_func_32_cigam(t_nm **nm,
		struct mach_header *header, struct load_command *lc,
		void const *ptr)
{
	uint32_t				i;
	struct load_command		*lc_next;

	if (nm == NULL || *nm == NULL || header == NULL || lc == NULL || ptr == NULL)
		ERROR_EXIT("Invalid arguments", __FILE__, NULL, NULL);
	i = 0;
	while (i++ < header->ncmds)
	{
		swap_load_command(lc, NX_UnknownByteOrder);
		if (lc->cmd == LC_SYMTAB)
		{
			swap_load_command(lc = (void*)lc, NX_UnknownByteOrder);
			return (save_output_32_cigam(nm, (struct symtab_command *)lc, ptr));
		}
		if ((void*)(lc_next = (void *)lc + lc->cmdsize) > (void*)(*nm)->end)
			ERROR_EXIT("Ptr lc over the end 2", __FILE__, del_nm, nm);
		swap_load_command(lc = (void*)lc, NX_UnknownByteOrder);
		lc = lc_next;
	}
	swap_mach_header(header = (struct mach_header*)ptr, NX_UnknownByteOrder);
	return (NULL);
}

t_symbol					*func_32_cigam(t_nm **nm, void *ptr,
		char const *name_bin)
{
	struct mach_header		*header;
	struct load_command		*lc;

	if (nm == NULL || *nm == NULL || ptr == NULL || name_bin == NULL)
		ERROR_EXIT("NM or CURS = NULL", __FILE__, del_nm, nm);
	if ((size_t)(*nm)->buff.st_size <= sizeof(struct mach_header))
		return (NULL);
	(*nm)->len_addr = LEN_32_BIT;
	swap_mach_header(header = (struct mach_header*)ptr, NX_UnknownByteOrder);
	(*nm)->magic = MH_CIGAM;
	if ((void*)(lc = (void*)ptr + sizeof(*header)) + sizeof(*lc) >
			(void*)(*nm)->end)
		ERROR_EXIT("Ptr lc over the end", __FILE__, del_nm, nm);
	return (loop_func_32_cigam(nm, header, lc, ptr));
}

static char					*get_symbol_32_2_cigam(struct segment_command *seg_cmd,
		struct section *sec, t_symbol const symbol, uint8_t *j)
{
	uint32_t				i;

	i = 0;
	printf("ncmd %d\n", seg_cmd->nsects);
	swap_segment_command(seg_cmd, 0);
	printf("ncmd %d\n", seg_cmd->nsects);
	while (i++ < seg_cmd->nsects)
	{
		swap_section(sec, seg_cmd->nsects, NX_UnknownByteOrder);
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
		sec = (struct section *)((char *)sec + sizeof(struct section));
	}
	swap_segment_command(seg_cmd, 0);
	return ("");
}

char						*get_symbol_32_cigam(t_symbol const symbol,
		void const *ptr)
{
	char					*ret;
	uint32_t				i;
	struct mach_header		*header;
	struct load_command		*lc;
	uint8_t					j;

	swap_mach_header(header = (struct mach_header*)ptr, 0);
	swap_load_command(lc = (void*)ptr + sizeof(*header), 0);
	i = 0;
	j = 0;
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			ret = get_symbol_32_2_cigam((void *)lc, (void *)lc + sizeof(
					struct segment_command), symbol, &j);
			if (ft_strlen(ret) > 0)
				return (ret);
		}
		swap_load_command(lc = (void *)lc + lc->cmdsize, 0);
	}
	return ("ERROR");
}