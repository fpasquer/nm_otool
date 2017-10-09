/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_cigam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 09:46:57 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/09 09:59:31 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

void					ft_swap_load_command(struct load_command *lc,
		enum NXByteOrder target_byte_order)
{
	if (lc == NULL || target_byte_order != NX_UnknownByteOrder)
		return ;
	lc->cmd = b_to_l(lc->cmd);
	lc->cmdsize = b_to_l(lc->cmdsize);
}

void					ft_swap_segment_command(struct segment_command *seg,
		enum NXByteOrder target_byte_order)
{
	if (seg == NULL || target_byte_order != NX_UnknownByteOrder)
		return ;
	seg->cmd = b_to_l(seg->cmd);
	seg->cmdsize = b_to_l(seg->cmdsize);
	seg->vmaddr = b_to_l(seg->vmaddr);
	seg->vmsize = b_to_l(seg->vmsize);
	seg->fileoff = b_to_l(seg->fileoff);
	seg->filesize = b_to_l(seg->filesize);
	seg->maxprot = b_to_l(seg->maxprot);
	seg->initprot = b_to_l(seg->initprot);
	seg->nsects = b_to_l(seg->nsects);
	seg->flags = b_to_l(seg->flags);
}

void					ft_swap_section(struct section *sec,
		uint32_t const nsects, enum NXByteOrder target_byte_order)
{
	uint32_t				i;

	if (sec == NULL || target_byte_order != NX_UnknownByteOrder)
		return ;
	i = 0;
	while (i < nsects)
	{
		sec[i].addr = b_to_l(sec->addr);
		sec[i].size = b_to_l(sec->size);
		sec[i].offset = b_to_l(sec->offset);
		sec[i].align = b_to_l(sec->align);
		sec[i].reloff = b_to_l(sec->reloff);
		sec[i].nreloc = b_to_l(sec->nreloc);
		sec[i].flags = b_to_l(sec->flags);
		sec[i].reserved1 = b_to_l(sec->reserved1);
		sec[i].reserved2 = b_to_l(sec->reserved2);
		i++;
	}
}

void					ft_swap_nlist(struct nlist *lst,
		uint32_t const nsyms, enum NXByteOrder target_byte_order)
{
	uint32_t				i;

	if (lst == NULL || target_byte_order != NX_UnknownByteOrder)
		return ;
	i = 0;
	while (i < nsyms)
	{
		lst[i].n_un.n_strx = b_to_l(lst[i].n_un.n_strx);
		lst[i].n_value = b_to_l(lst[i].n_value);
		i++;
	}
}

void					ft_swap_symtab_command(struct symtab_command *cmd,
		enum NXByteOrder target_byte_order)
{
	if (cmd == NULL || target_byte_order != NX_UnknownByteOrder)
		return ;
	cmd->cmd = b_to_l(cmd->cmd);
	cmd->cmdsize = b_to_l(cmd->cmdsize);
	cmd->symoff = b_to_l(cmd->symoff);
	cmd->nsyms = b_to_l(cmd->nsyms);
	cmd->stroff = b_to_l(cmd->stroff);
	cmd->strsize = b_to_l(cmd->strsize);
}
