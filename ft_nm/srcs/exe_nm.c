/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_nm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 11:42:21 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/24 18:03:27 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

#define INIT_FUNC(i, k, ptr) func[i].key = k; func[i].f = ptr;

bool						exe_nm(t_nm **nm)
{
	unsigned int			i;
	t_func_nm				func[NB_FUNC];

	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
	INIT_FUNC(0, MH_MAGIC, func_32);
	INIT_FUNC(1, MH_CIGAM, func_32_cigan);
	INIT_FUNC(2, MH_MAGIC_64, func_64);
	INIT_FUNC(3, MH_CIGAM_64, func_64_cigan);
	INIT_FUNC(4, FAT_MAGIC, func_fat_magic);
	INIT_FUNC(5, FAT_CIGAM, func_fat_cigam);
	INIT_FUNC(6, ERROR, NULL);
	(*nm)->magic_number = *(int*)(*nm)->curs;
	i = 0;
	while (func[i].key != ERROR)
		if (func[i++].key == (*nm)->magic_number)
			return (func[i - 1].f(nm));
	ft_putstr_fd("***Magic number invalable ", STDERR_FILENO);
																				printf("magic number = 0x%x %s \n", (*nm)->magic_number, (*nm)->p_name_cpy);
	return (false);
}
