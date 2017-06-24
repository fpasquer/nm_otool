/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:38:13 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/24 12:41:26 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

bool						func_32(t_nm **nm)
{
	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
																				printf("Magic number for 32 bits = 0x%x\n", (*nm)->magic_number);
	return (true);
}
