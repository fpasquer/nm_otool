/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_nm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 10:59:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/23 11:11:05 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

void						del_nm(void *nm)
{
	t_nm					**nm_ptr;

	if ((nm_ptr = (t_nm**)nm) == NULL)
		ERROR_EXIT("nm NULL", __FILE__, NULL, NULL);
	if ((*nm_ptr) != NULL)
		ft_memdel((void**)nm_ptr);
}
