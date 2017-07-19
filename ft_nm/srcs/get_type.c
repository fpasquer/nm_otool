/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 16:16:48 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/19 16:17:30 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

char						*get_type(t_nm const **nm, t_symbol const symbol)
{
	uint8_t					type;
	uint8_t					ext;

	ext = symbol.type & N_EXT;
	if ((type = symbol.type & N_TYPE) == N_UNDF)
	{
		if (symbol.value != 0)
			return (ext == 0 ? "c" : "C");
		return (ext == 0 ? "u" : "U");
	}
	else if (type == N_ABS)
		return (ext == 0 ? "a" : "A");
	else if (type == N_SECT)
		return ((*nm)->magic == MH_MAGIC_64 ? get_symbol_64(nm, symbol) :
				get_symbol_32(nm, symbol));
	else if (type == N_PBUD)
		return (ext == 0 ? "u" : "U");
	else if (type == N_INDR)
		return (ext == 0 ? "i" : "I");
	else if ((symbol.type & N_STAB) != 0)
		return ("-");
	return ("(?)");
}