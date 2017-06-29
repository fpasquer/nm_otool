/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:41:54 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/29 21:55:57 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

static bool					print_output(t_nm **nm, unsigned long nsyms,
		unsigned long symoff, unsigned long stroff)
{
	unsigned long			i;
	char					*stringTable;
	struct nlist_64			*array;

	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM = NULL 2", __FILE__, NULL, NULL);
	;
	if ((void*)(stringTable = (void*)(*nm)->data + stroff) > (void*)(*nm)->end)
		ERROR_EXIT("stringTable adr over", __FILE__, del_nm, nm);
	if ((void*)(array = (void*)(*nm)->data + symoff) > (void*)(*nm)->end)
		ERROR_EXIT("array adr over", __FILE__, del_nm, nm);
	i = 0;
	while (i < nsyms)
		ft_putendl(stringTable + array[i++].n_un.n_strx);
	return (true);
}

static bool					loop_func_64(t_nm **nm, struct mach_header_64
		*header, struct load_command *lc)
{
	size_t					i;
	struct symtab_command	*sym;

	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM = NULL 3", __FILE__, NULL, NULL);
	i = 0;
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			if ((void*)(sym = (struct symtab_command*)lc) > (void*)(*nm)->end)
				ERROR_EXIT("sym adr over", __FILE__, del_nm, nm);
			return (print_output(nm, sym->nsyms, sym->symoff, sym->stroff));
		}
		if ((void*)(lc = (void*)lc + lc->cmdsize) > (void*)(*nm)->end)
				ERROR_EXIT("lc adr over 2", __FILE__, del_nm, nm);
	}
	return (false);
}

bool						func_64(t_nm **nm)
{
	struct mach_header_64	*header;
	struct load_command		*lc;

	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
																				printf("Magic number for 64 bits = 0x%x\n", (*nm)->magic_number);
	header = (struct mach_header_64*)(*nm)->data;
	if ((void*)(lc = (struct load_command*)((*nm)->data + sizeof(*header))) >
			(void*)(*nm)->end)
		ERROR_EXIT("lc adr over 1", __FILE__, del_nm, nm);
	return (loop_func_64(nm, header, lc));
}
