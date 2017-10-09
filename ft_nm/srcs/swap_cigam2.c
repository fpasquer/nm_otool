/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_cigam2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 09:51:36 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/09 09:59:50 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

void						ft_swap_mach_header(struct mach_header *header,
	enum NXByteOrder target_byte_order)
{
	if (header == NULL || target_byte_order != NX_UnknownByteOrder)
		return ;
	header->magic = b_to_l(header->magic);
	header->cputype = b_to_l(header->cputype);
	header->cpusubtype = b_to_l(header->cpusubtype);
	header->filetype = b_to_l(header->filetype);
	header->ncmds = b_to_l(header->ncmds);
	header->sizeofcmds = b_to_l(header->sizeofcmds);
	header->flags = b_to_l(header->flags);
}

uint32_t					b_to_l(uint32_t num)
{
	return (((num >> 24) & 0xff) |
			((num << 8) & 0xff0000) |
			((num >> 8) & 0xff00) |
			((num << 24) & 0xff000000));
}
