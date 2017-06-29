/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:38:13 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/29 12:31:30 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

bool						func_32(t_nm **nm)
{
	struct mach_header		*header;
	struct segment_command	*segment;

	if (nm == NULL || *nm == NULL || (*nm)->curs == NULL)
		ERROR_EXIT("NM or CURS = NULL", __FILE__, del_nm, nm);
																				printf("Magic number for 32 bits = 0x%x\n", (*nm)->magic_number);
	if ((*nm)->buff.st_size < sizeof(*header))
		ERROR_EXIT("Error size", __FILE__, del_nm, nm);
	header = (struct mach_header*)(*nm)->curs;
	return (true);
}
