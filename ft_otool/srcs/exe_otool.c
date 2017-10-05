/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_otool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 11:13:43 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/05 17:02:28 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

t_func_struct				g_funcs[] =
{
	{MH_MAGIC, func_32},
	{MH_CIGAM, func_32},
	{MH_MAGIC_64, func_64},
	{MH_CIGAM_64, func_64},
	{FAT_MAGIC, func_fat},
	{FAT_CIGAM, func_fat}
};

void						*exe_otool(t_otool *otool, char const *name,
		void const *ptr)
{
	unsigned int			i;
	uint32_t				magic_number;

	if (name == NULL || ptr == NULL)
		return ((void*)put_error_file("name == NULL"));
	if ((void*)(ptr + sizeof(magic_number)) >= (void*)otool->end)
		return ((void*)put_error_file("Over the end hjxgv cjzhgvx xj"));
	magic_number = *(uint32_t*)ptr;
	i = 0;
	while (i < NB_FUNC)
		if (magic_number == g_funcs[i++].key)
			return (g_funcs[i - 1].func(otool, name, ptr));
	return (NULL);
}
