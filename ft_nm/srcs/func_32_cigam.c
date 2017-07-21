/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_32_cigan.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:40:59 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/21 18:18:24 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

t_symbol					*func_32_cigam(t_nm **nm, void *ptr,
		char const *name_bin)
{
	int						magic_number = 0;

	if (nm == NULL || *nm == NULL || ptr == NULL || name_bin == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
																				printf("Magic number for 32 bits cigam = 0x%x\n", magic_number);
	return (NULL);
}
