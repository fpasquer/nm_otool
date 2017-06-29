/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:38:13 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/29 21:22:13 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

bool						func_32(t_nm **nm)
{
	if (nm == NULL || *nm == NULL || (*nm)->data == NULL)
		ERROR_EXIT("NM or CURS = NULL", __FILE__, del_nm, nm);
																				printf("Magic number for 32 bits = 0x%x\n", (*nm)->magic_number);
	return (true);
}
