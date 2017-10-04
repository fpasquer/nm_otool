/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_nm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 11:42:21 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/04 14:11:04 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

t_func_nm					g_func[NB_FUNC] =
{
	{MH_MAGIC, func_32},
	{MH_CIGAM, func_32_cigam},
	{MH_MAGIC_64, func_64},
	{MH_CIGAM_64, func_64_cigam},
	{FAT_MAGIC, func_fat_magic},
	{FAT_CIGAM, func_fat_cigam}
};

t_symbol					*exe_nm(t_nm **nm, char const *name_bin, void *ptr)
{
	unsigned int			i;
	uint32_t				magic_number;
	size_t					len;

	if (nm == NULL || *nm == NULL || name_bin == NULL || ptr == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
	if ((size_t)(*nm)->buff.st_size > sizeof(uint32_t))
	{
		magic_number = *(uint32_t*)ptr;
		i = 0;
		while (i < NB_FUNC)
			if (g_func[i++].key == magic_number)
				return (g_func[i - 1].f((t_nm **)nm, ptr, name_bin));
		len = ft_strlen(AR_EFMT1);
		if ((*nm)->buff.st_size > (off_t)len + SARMAG && ft_strncmp(ARMAG, ptr,
				SARMAG) == 0 && ft_strncmp(AR_EFMT1, ptr + SARMAG, len) == 0)
			return (func_armag_magic((t_nm **)nm, ptr + SARMAG, name_bin));
	}
	ft_putstr_fd("***Magic number invalable ", STDERR_FILENO);
	put_error_binaries(name_bin);
	return (NULL);
}
