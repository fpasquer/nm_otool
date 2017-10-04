/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_nm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 10:59:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/04 09:00:44 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

void						del_nm(void *nm)
{
	t_nm					**nm_ptr;

	if ((nm_ptr = (t_nm**)nm) == NULL || (*nm_ptr) == NULL)
		return ;
	if ((*nm_ptr)->p_name_cpy != NULL)
		ft_memdel((void**)&(*nm_ptr)->p_name_cpy);
	if ((*nm_ptr)->fd > 0)
		close((*nm_ptr)->fd);
	if ((*nm_ptr) != NULL)
		ft_memdel((void**)nm_ptr);
	print_cache();
}
