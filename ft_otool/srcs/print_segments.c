/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_segments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 10:18:11 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/26 15:20:15 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

void						print_header(char const *name, char const *segname,
		char const *sectname)
{
	if (name == NULL || segname == NULL || sectname == NULL)
		return ;
	add_cache_print(name);
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

void						print_value(uint64_t const addr, size_t len, uint64_t length)
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

void						print_line(uint64_t length, void const *ptr)
{
	unsigned char			c;
	unsigned int			i;
	char					mem[3];

	if (length <= 0 || ptr == NULL)
		return ;
	i = 0;
	while (i < NB_EACH_LINE && i < length)
	{
		ft_bzero(mem, sizeof(mem));
		c = *(unsigned char*)(ptr + i++);
		ft_utoa_base_tab(c, 16, mem, 2);
		place_value(mem, 2);
		add_cache_print(mem);
		add_cache_print(" ");
	}
	add_cache_print("\n");
}