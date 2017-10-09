/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_fat_cigam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 17:49:18 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/09 07:26:41 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

#define NAME {add_cache_print(g_cpu_str[j - 1].str); break ;}
#define V int ret;int j; uint32_t i;struct fat_arch *arch;

t_cpu_type_str				g_cpu_str[] =
{
	{CPU_TYPE_ANY, " (for architecture ) 1:\n"},
	{CPU_TYPE_VAX, " (for architecture ) 2:\n"},
	{CPU_TYPE_MC680x0, " (for architecture ) 3:\n"},
	{CPU_TYPE_X86, " (for architecture i386):\n"},
	{CPU_TYPE_I386, " (for architecture ) 5:\n"},
	{CPU_TYPE_X86_64, " (for architecture x86_64):\n"},
	{CPU_TYPE_MC98000, " (for architecture ) 6:\n"},
	{CPU_TYPE_HPPA, " (for architecture ) 7:\n"},
	{CPU_TYPE_ARM, " (for architecture ) 8:\n"},
	{CPU_TYPE_ARM64, " (for architecture ) 9:\n"},
	{CPU_TYPE_MC88000, " (for architecture ) 10:\n"},
	{CPU_TYPE_SPARC, " (for architecture ) 11:\n"},
	{CPU_TYPE_I860, " (for architecture ) 12:\n"},
	{CPU_TYPE_POWERPC, " (for architecture ppc):\n"},
	{CPU_TYPE_POWERPC64, " (for architecture pp64) :\n"},
	{0, ""}
};

uint32_t					b_to_l(uint32_t num)
{
	return (((num >> 24) & 0xff) |
			((num << 8) & 0xff0000) |
			((num >> 8) & 0xff00) |
			((num << 24) & 0xff000000));
}

static int					cpu_and_cpusub_type_true(t_nm **nm,
		char const *name_bin, uint32_t offset_arch, void *ptr)
{
	t_symbol				*symbol;

	if (ptr == NULL || name_bin == NULL || nm == NULL || *nm == NULL)
		return (-1);
	if (ptr + offset_arch > (void*)(*nm)->end)
		return (-1);
	if ((symbol = exe_nm(nm, name_bin, ptr + offset_arch)) != NULL)
	{
		gestion_symbols(nm, &symbol, name_bin, ptr + offset_arch);
		return (true);
	}
	return (-1);
}

static int					loop_fat(t_nm **nm, const uint32_t end, void *ptr,
		char const *name)
{
	int						ret;
	uint32_t				i;
	struct fat_arch			*arch;

	if (nm == NULL || *nm == NULL || ptr == NULL || name == NULL)
		ERROR_INT("NM = NULL 2", __FILE__, NULL, NULL);
	i = 0;
	if ((void*)(arch = (void*)ptr + sizeof(struct fat_header*)) >
			(void*)(*nm)->end)
		ERROR_INT("Ptr arch over the end", __FILE__, del_nm, nm);
	while (i++ < end)
	{
		if ((b_to_l(arch->cputype) == CPU_TYPE &&
				b_to_l(arch->cpusubtype & CPU_SUBTYPE_MASK) == CPU_SUB_TYPE))
		{
			ret = cpu_and_cpusub_type_true(nm, name, b_to_l(arch->offset), ptr);
			reset_struct_nm(nm, ptr + b_to_l(arch->offset));
			return (ret);
		}
		if ((void*)(arch = (void*)arch + sizeof(*arch)) > (void*)(*nm)->end)
			ERROR_INT("Ptr arch over the end 2", __FILE__, del_nm, nm);
	}
	return (false);
}

static int					loop_fat2(t_nm **nm, const uint32_t end, void *ptr,
	char const *name_bin)
{
	V;
	if (nm == NULL || *nm == NULL || ptr == NULL || name_bin == NULL)
		ERROR_INT("NM = NULL 2", __FILE__, NULL, NULL);
	i = 0;
	ret = true;
	if ((void*)(arch = ptr + sizeof(struct fat_header*)) > (void*)(*nm)->end)
		ERROR_INT("Ptr arch over the end", __FILE__, del_nm, nm);
	while (i++ < end && (j = 0) == 0 && ret == true)
	{
		if (end > 1)
			add_cache_print("\n");
		add_cache_print(name_bin);
		if (end == 1)
			add_cache_print(":\n");
		while (end > 1 && g_cpu_str[j].key != 0)
			if (g_cpu_str[j++].key == b_to_l(arch->cputype))
				NAME;
		ret = cpu_and_cpusub_type_true(nm, name_bin, b_to_l(arch->offset), ptr);
		if ((void*)(arch = (void*)arch + sizeof(*arch)) > (void*)(*nm)->end)
			ERROR_INT("Ptr arch over the end 2", __FILE__, del_nm, nm);
	}
	reset_struct_nm(nm, ptr + b_to_l(arch->offset));
	(*nm)->fat = true;
	return (ret);
}

t_symbol					*func_fat_cigam(t_nm **nm, void *ptr,
		char const *name_bin)
{
	int						ret;
	struct fat_header		*header;

	if (nm == NULL || *nm == NULL || ptr == NULL || name_bin == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
	if ((size_t)(*nm)->buff.st_size <= sizeof(struct fat_header))
		return (NULL);
	(*nm)->fat = true;
	header = (struct fat_header*)ptr;
	if ((ret = loop_fat(nm, b_to_l(header->nfat_arch), ptr, name_bin)) == false)
	{
		(*nm)->fat = false;
		ret = loop_fat2(nm, b_to_l(header->nfat_arch), ptr, name_bin);
	}
	return (ret == true ? ptr : NULL);
}
