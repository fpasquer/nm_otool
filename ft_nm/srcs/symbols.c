/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 15:13:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/09 11:52:34 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

static void					sort_symbols(t_nm *nm, t_symbol *symbol)
{
	if (nm == NULL || symbol == NULL)
		ERROR_VOID("Symbol or nm NULL", __FILE__, NULL, NULL);
	if ((nm->flags & F_N_MIN) != 0)
	{
		ft_qsort(symbol, nm->nb_symbol, sizeof(*symbol), sort_numerically);
		sort_type_ascii(symbol, N_UNDF, nm->nb_symbol);
		if ((nm->flags & F_A_MIN) != 0)
			sort_type_ascii_debug(symbol, N_UNDF, nm->nb_symbol, 0);
	}
	else if ((nm->flags & F_P_MIN) != 0)
		return ;
	else
		ft_qsort(symbol, nm->nb_symbol, sizeof(*symbol), sort_ascii);
}

static void					del_symbols(t_symbol **symbol,
		uint32_t const nb_symbol)
{
	uint32_t				i;
	t_symbol				*curs;

	if (symbol == NULL)
		return ;
	curs = (*symbol);
	i = 0;
	while (i < nb_symbol)
		if (curs[i++].name != NULL)
			ft_memdel((void**)&curs[i - 1].name);
	ft_memdel((void**)symbol);
}

void						gestion_symbols(t_nm **nm, t_symbol **symbol,
		char const *name_file, void const *ptr)
{
	if (nm == NULL || *nm == NULL || symbol == NULL || *symbol == NULL)
		ERROR_VOID("Invalid values", __FILE__, del_nm, nm);
	sort_symbols(*nm, *symbol);
	print_symbols((t_nm const **)nm, *symbol, name_file, ptr);
	(*nm)->print = false;
	del_symbols(symbol, (*nm)->nb_symbol);
}
