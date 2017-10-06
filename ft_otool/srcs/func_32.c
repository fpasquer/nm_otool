/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 11:45:09 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/06 12:07:09 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

#define STRUCT struct segment_command*

static void					increment_var(uint32_t *offset, uint32_t *value,
		uint64_t *size)
{
	if (offset != NULL && value != NULL && size != NULL)
	{
		*offset += NB_EACH_LINE;
		*value += NB_EACH_LINE;
		*size -= NB_EACH_LINE;
	}
}

static void					*get_segment_32(t_otool *otool, char const *name,
		struct segment_command *sec_cmd, void const *ptr)
{
	uint32_t				offset;
	uint32_t				v;
	uint64_t				s;
	struct section			*sec;

	if (otool == NULL || sec_cmd == NULL || ptr == NULL || name == NULL)
		return ((void*)put_error_file("Otool NULL asjda sjdkh ahjsd"));
	if ((void*)(sec = (void*)sec_cmd + sizeof(*sec_cmd)) + sizeof(*sec) >=
			(void*)otool->end)
		return ((void*)put_error_file("Over the end dqwid qjwd gjqwg"));
	print_header(name, sec->segname, sec->sectname, otool);
	s = B_TO_L(otool->cigam, sec->size);
	offset = B_TO_L(otool->cigam, sec->offset);
	v = ft_strcmp(sec_cmd->segname, "") != 0 ? offset : 0;
	while (1)
	{
		print_value(v + B_TO_L(otool->cigam, sec_cmd->vmaddr), LEN_32_BIT, s);
		if ((void*)(ptr + offset + NB_EACH_LINE) > otool->end)
			return ((void*)put_error_file("Over the end dsafsdasdfdassa"));
		print_line(s, ptr + offset, otool);
		if (s <= NB_EACH_LINE)
			break ;
		increment_var(&offset, &v, &s);
	}
	return (NULL);
}

void						*func_32(t_otool *otool, char const *name,
		void const *ptr)
{
	uint32_t				seg;
	uint32_t				i;
	struct mach_header		*head;
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
		if (lc->cmd == seg && (!ft_strcmp(((STRUCT)lc)->segname, "") ||
				!ft_strcmp(((STRUCT)lc)->segname, SEG_TEXT)))
			return (get_segment_32(otool, name, (STRUCT)lc, ptr));
		else if ((void*)(lc = (void*)lc + B_TO_L(otool->cigam, lc->cmdsize)) +
				sizeof(*lc) > (void*)otool->end)
			return ((void*)put_error_file("Over the end adasdasdasdasddgfbf"));
	return (NULL);
}
