/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_32_cigan.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:40:59 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/30 18:10:03 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

bool						func_32_cigan(t_nm const **nm)
{
	int						magic_number = 0;

	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
																				printf("Magic number for 32 bits cigan = 0x%x\n", magic_number);
	return (true);
}
