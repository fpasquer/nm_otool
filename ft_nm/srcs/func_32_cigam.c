/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_32_cigam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:40:59 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/05 10:26:50 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

#define I2 i = 0; j = 0; ret = NULL;
#define I lc[0] = (void*)ptr + sizeof(*header); I2
#define R2 swap_segment_command(seg_cmd, 0);
#define R swap_section(start, seg_cmd->nsects, 0); R2
#define END if (ft_strlen(ret) > 0)break ;
#define INIT2 (*nm)->nb_symbol = sym->nsyms;
#define INIT i = 0; str_table = (void*)ptr + sym->stroff; INIT2

static t_symbol				*save_output_32_cigam(t_nm **nm,
		struct symtab_command *sym, void const *ptr)
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
	swap_nlist(tab = (void*)ptr + sym->symoff, sym->nsyms, NX_UnknownByteOrder);
	INIT;
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
	t_symbol				*ret;
	struct load_command		*lc_next;

	if (nm == NULL || *nm == NULL || header == NULL || lc == NULL)
		ERROR_EXIT("Invalid arguments", __FILE__, NULL, NULL);
	i = 0;
	ret = NULL;
	while (i++ < header->ncmds)
	{
		swap_load_command(lc, NX_UnknownByteOrder);
		if (lc->cmd == LC_SYMTAB)
		{
			swap_load_command(lc = (void*)lc, NX_UnknownByteOrder);
			ret = save_output_32_cigam(nm, (struct symtab_command *)lc, ptr);
			break ;
		}
		if ((void*)(lc_next = (void *)lc + lc->cmdsize) > (void*)(*nm)->end)
			ERROR_EXIT("Ptr lc over the end 2", __FILE__, del_nm, nm);
		swap_load_command(lc, NX_UnknownByteOrder);
		if ((void*)(lc = lc_next) > (void*)(*nm)->end)
			break ;
	}
	swap_mach_header(header, NX_UnknownByteOrder);
	return (ret);
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

static char					*get_symbol_32_2_cigam(
		struct segment_command *seg_cmd, struct section *sec,
		t_symbol const symbol, uint8_t *j)
{
	char					mem[16];
	uint32_t				i;
	struct section			*start;

	i = 0;
	swap_segment_command(seg_cmd, NX_UnknownByteOrder);
	swap_section(start = sec, seg_cmd->nsects, NX_UnknownByteOrder);
	while (seg_cmd->nsects > 0 && i++ < seg_cmd->nsects)
	{
		if (++(*j) == symbol.sect)
		{
			ft_strcpy(mem, sec->sectname);
			R;
			if (ft_strcmp(mem, SECT_DATA) == 0)
				return ((symbol.type & N_EXT) == 0 ? "d" : "D");
			else if (ft_strcmp(mem, SECT_BSS) == 0)
				return ((symbol.type & N_EXT) == 0 ? "b" : "B");
			else if (ft_strcmp(mem, SECT_TEXT) == 0)
				return ((symbol.type & N_EXT) == 0 ? "t" : "T");
			return ((symbol.type & N_EXT) == 0 ? "s" : "S");
		}
		sec = (struct section *)((char *)sec + sizeof(struct section));
	}
	R;
	return ("");
}

/*
** lc[0] = lc
** lc[1] = lc_next
*/

char						*get_symbol_32_cigam(t_symbol const symbol,
		void const *ptr)
{
	char					*ret;
	uint32_t				i;
	struct mach_header		*header;
	struct load_command		*lc[2];
	uint8_t					j;

	swap_mach_header(header = (struct mach_header*)ptr, NX_UnknownByteOrder);
	I;
	while (i++ < header->ncmds)
	{
		swap_load_command(lc[0], NX_UnknownByteOrder);
		if (lc[0]->cmd == LC_SEGMENT)
		{
			swap_load_command(lc[0], NX_UnknownByteOrder);
			ret = get_symbol_32_2_cigam((void *)lc[0], (void *)lc[0] + sizeof(
					struct segment_command), symbol, &j);
			END;
			swap_load_command(lc[0], NX_UnknownByteOrder);
		}
		lc[1] = (void *)lc[0] + lc[0]->cmdsize;
		swap_load_command(lc[0], NX_UnknownByteOrder);
		lc[0] = lc[1];
	}
	swap_mach_header(header, NX_UnknownByteOrder);
	return (ret);
}
