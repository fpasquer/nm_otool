/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 11:50:05 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/26 13:16:20 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

#define STRUCT struct segment_command_64*

static void					*get_segment_64(t_otool *otool, char const *name,
		struct segment_command_64 *secCmd, void const *ptr)
{
	uint32_t				offset;
	uint64_t				size;
	struct section_64		*sec;

	if (otool == NULL || secCmd == NULL || ptr == NULL || name == NULL)
		return ((void*)put_error_file("Otool NULL asjda sjdkh ahjsd"));
	if ((void*)(sec = (void*)secCmd + sizeof(*secCmd)) + sizeof(*sec) >=
			(void*)otool->end)
		return ((void*)put_error_file("Over the end dqwid qjwd gjqwg"));
	print_header(name, sec->segname, sec->sectname);
	/*
		print_line(addr + i, length - i, len, ptr + i);
	*/
	size = sec->size;
	offset = sec->offset;
	while (1)
	{
		print_line(offset + secCmd->vmaddr, size, LEN_64_BIT, ptr + offset);
		if (size < NB_EACH_LINE)
			break ;
		offset += NB_EACH_LINE;
		size -= NB_EACH_LINE;
	}
	return (NULL);
}

void						*func_64(t_otool *otool, char const *name,
		void const *ptr)
{
	uint32_t				seg;
	uint32_t				i;
	struct mach_header_64	*head;
	struct load_command		*lc;

	if (otool == NULL || name == NULL || ptr == NULL || (i = 0))
		return (NULL);
	if (((void*)(head = (struct mach_header_64 *)ptr)) + sizeof(head) >=
			(void*)otool->end)
		return ((void*)put_error_file("Over the end asjdkha ksjdhasjda lksd"));
	otool->cigam = (head->magic == MH_CIGAM_64) ? true : false;
	otool->bits64 = true;
	if ((void*)(lc = (void*)ptr + sizeof(*head)) + sizeof(*lc) >=
			(void*)otool->end)
		return ((void*)put_error_file("Over the end adhaasdsjda lksd"));
	seg = (otool->cigam == true) ? b_to_l_endian(LC_SEGMENT_64) : LC_SEGMENT_64;
	while (i++ < head->ncmds)
		if (lc->cmd == seg &&
				!ft_strcmp(((struct segment_command_64*)lc)->segname, SEG_TEXT))
			return (get_segment_64(otool, name, (STRUCT)lc, ptr));
		else if ((void*)(lc = (void*)lc + lc->cmdsize) + sizeof(*lc) >=
				(void*)otool->end)
			return ((void*)put_error_file("Over the end adasdasdasdasdd"));
	return (NULL);
}