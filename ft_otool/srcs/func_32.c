/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 11:45:09 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/25 15:29:52 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

#define STRUCT struct segment_command*

static void					*get_segment_32(t_otool *otool, char const *name,
		struct segment_command *secCmd, void const *ptr)
{
	struct section		*sec;

	if (otool == NULL || secCmd == NULL || ptr == NULL || name == NULL)
		return ((void*)put_error_file("Otool NULL asjda sjdkh ahjsd"));
	if ((void*)(sec = (void*)secCmd + sizeof(*secCmd)) + sizeof(*sec) >=
			(void*)otool->end)
		return ((void*)put_error_file("Over the end dqwid qjwd gjqwg"));
	print_header(name, sec->segname, sec->sectname);
	print_line(sec->offset + 0x1000, sec->size, LEN_32_BIT, ptr +
			sec->offset);
	return (NULL);
}

void						*func_32(t_otool *otool, char const *name,
		void const *ptr)
{
	uint32_t				seg;
	uint32_t				i;
	struct mach_header	*head;
	struct load_command		*lc;

	if (otool == NULL || name == NULL || ptr == NULL || (i = 0))
		return (NULL);
	if (((void*)(head = (struct mach_header *)ptr)) + sizeof(head) >=
			(void*)otool->end)
		return ((void*)put_error_file("Over the end asjdkha ksjdhasjda lksd"));
	otool->cigam = (head->magic == MH_CIGAM) ? true : false;
	otool->bits64 = false;
	if ((void*)(lc = (void*)ptr + sizeof(*head)) + sizeof(*lc) >=
			(void*)otool->end)
		return ((void*)put_error_file("Over the end adhaasdsjda lksd"));
	seg = (otool->cigam == true) ? b_to_l_endian(LC_SEGMENT) : LC_SEGMENT;
	while (i++ < head->ncmds)
		if (lc->cmd == seg &&
				!ft_strcmp(((struct segment_command*)lc)->segname, SEG_TEXT))
			return (get_segment_32(otool, name, (STRUCT)lc, ptr));
		else if ((void*)(lc = (void*)lc + lc->cmdsize) + sizeof(*lc) >=
				(void*)otool->end)
			return ((void*)put_error_file("Over the end adasdasdasdasdd"));
	return (NULL);
}