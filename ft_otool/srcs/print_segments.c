/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_segments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 10:18:11 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/06 12:00:39 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

t_cpu_type_str				g_cpu_str[] =
{
	{CPU_TYPE_ANY, " (architecture ) 1"},
	{CPU_TYPE_VAX, " (architecture ) 2"},
	{CPU_TYPE_MC680x0, " (architecture ) 3"},
	{CPU_TYPE_X86, " (architecture i386)"},
	{CPU_TYPE_I386, " (architecture ) 5"},
	{CPU_TYPE_X86_64, " (architecture x86_64)"},
	{CPU_TYPE_MC98000, " (architecture ) 6"},
	{CPU_TYPE_HPPA, " (architecture ) 7"},
	{CPU_TYPE_ARM, " (architecture ) 8"},
	{CPU_TYPE_ARM64, " (architecture ) 9"},
	{CPU_TYPE_MC88000, " (architecture ) 10"},
	{CPU_TYPE_SPARC, " (architecture ) 11"},
	{CPU_TYPE_I860, " (architecture ) 12"},
	{CPU_TYPE_POWERPC, " (architecture ppc)"},
	{CPU_TYPE_POWERPC64, " (architecture pp64)"},
	{0, ""}
};

void						print_header(char const *name, char const *segname,
		char const *sectname, t_otool *otool)
{
	int						i;

	if (name == NULL || segname == NULL || sectname == NULL || otool == NULL)
		return ;
	add_cache_print(name);
	i = 0;
	if (otool->end_seg > 1)
		while (g_cpu_str[i].key != 0)
			if (g_cpu_str[i++].key == otool->cpu_type)
			{
				add_cache_print(g_cpu_str[i - 1].str);
				break ;
			}
	add_cache_print(":\nContents of (");
	add_cache_print(segname);
	add_cache_print(",");
	add_cache_print(sectname);
	add_cache_print(") section\n");
}

static void					place_value(char *buff, size_t max)
{
	size_t					len;

	if (buff == NULL || max <= 0)
		return ;
	len = ft_strlen(buff);
	while (len-- > 0)
		buff[--max] = buff[len];
	while (max-- > 0)
		buff[max] = '0';
}

void						print_value(uint64_t const addr, size_t len,
		uint64_t length)
{
	char					tab[LEN_64_BIT + 1];

	if (length <= 0)
		return ;
	ft_bzero(tab, sizeof(char) * (LEN_64_BIT + 1));
	ft_utoa_base_tab(addr, 16, tab, LEN_64_BIT);
	place_value(tab, len);
	add_cache_print(tab);
	add_cache_print("\t");
}

void						print_line(uint64_t length, void const *ptr,
		t_otool *otool)
{
	unsigned char			c;
	unsigned int			i;
	char					mem[3];

	if (length <= 0 || ptr == NULL || otool == NULL)
		return ;
	i = 0;
	while (i < NB_EACH_LINE && i < length)
	{
		ft_bzero(mem, sizeof(mem));
		c = *(unsigned char*)(ptr + i++);
		ft_utoa_base_tab(c, 16, mem, 2);
		place_value(mem, 2);
		add_cache_print(mem);
		if (otool->cpu_type != CPU_TYPE_POWERPC || (i % 4) == 0)
			add_cache_print(" ");
	}
	add_cache_print("\n");
}
