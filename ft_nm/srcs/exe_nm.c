/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_nm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 11:42:21 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/15 15:38:15 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

#define INIT_FUNC(i, k, ptr) func[i].key = k; func[i].f = ptr;

t_symbol					*exe_nm(t_nm **nm)
{
	unsigned int			i;
	uint32_t				magic_number;
	t_func_nm				func[NB_FUNC];

	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
	INIT_FUNC(0, MH_MAGIC, func_32);
	INIT_FUNC(1, MH_CIGAM, func_32_cigan);
	INIT_FUNC(2, MH_MAGIC_64, func_64);
	INIT_FUNC(3, MH_CIGAM_64, func_64_cigan);
	INIT_FUNC(4, FAT_MAGIC, func_fat_magic);
	INIT_FUNC(5, FAT_CIGAM, func_fat_cigam);
	magic_number = *(int*)(*nm)->data;
	i = 0;
	while (i < NB_FUNC)
		if (func[i++].key == magic_number)
			return (func[i - 1].f((t_nm **)nm));
	ft_putstr_fd("***Magic number invalable ", STDERR_FILENO);
																				printf("magic number = 0x%x %s \n", magic_number, (*nm)->p_name_cpy);
	return (NULL);
}
