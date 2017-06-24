/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_64_cigan.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:42:44 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/24 12:42:59 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

bool						func_64_cigan(t_nm **nm)
{
	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
																				printf("Magic number for 64 bits cigan = 0x%x\n", (*nm)->magic_number);
	return (true);
}
