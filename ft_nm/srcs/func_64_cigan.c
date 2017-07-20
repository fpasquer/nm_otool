/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_64_cigan.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 12:42:44 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/20 15:55:11 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

t_symbol					*func_64_cigan(t_nm **nm, void *ptr)
{
	int						magic_number = 0;

	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
																				printf("Magic number for 64 bits cigan = 0x%x, ptr = %p\n", magic_number, ptr);
	return (NULL);
}
