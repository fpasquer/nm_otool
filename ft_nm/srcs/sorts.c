/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 15:20:35 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/20 14:29:08 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

int							sort_ascii(void const *a, void const *b)
{
	int						ret;
	t_symbol				*a_cpy;
	t_symbol				*b_cpy;

	a_cpy = (t_symbol *)a;
	b_cpy = (t_symbol *)b;
	if ((ret = ft_strcmp(a_cpy->name, b_cpy->name)) == 0)
	{
		if (a_cpy->value > b_cpy->value)
			ret = 1;
		else if (a_cpy->value == b_cpy->value)
			ret = 0;
		else
			ret = -1;
	}
	return (ret);
}

int							sort_numerically(void const *a, void const *b)
{
	t_symbol				*a_cpy;
	t_symbol				*b_cpy;

	a_cpy = (t_symbol *)a;
	b_cpy = (t_symbol *)b;
	if (a_cpy->value > b_cpy->value)
		return (1);
	else if (a_cpy->value == b_cpy->value)
	{
		if ((a_cpy->type & N_STAB) == 0 && (b_cpy->type & N_STAB) == 0)
		{
			if ((a_cpy->type & N_TYPE) != N_UNDF && (b_cpy->type & N_TYPE) == N_UNDF)
				return (1);
			else if ((a_cpy->type & N_TYPE) == N_UNDF && (b_cpy->type & N_TYPE) == N_UNDF)
				return (0);
		}
		else if ((a_cpy->type & N_STAB) != 0 && (b_cpy->type & N_STAB) == 0)
			return (1);
		else if ((a_cpy->type & N_STAB) != 0 && (b_cpy->type & N_STAB) != 0)
			return (0);
	}
	return (-1);
}

void						sort_type_ascii_debug(t_symbol *symbol,
		uint32_t type, uint32_t end_symbol, uint64_t value)
{
	uint32_t				i;
	t_symbol				*start;
	size_t					nb_symbol;

	if (symbol == NULL || end_symbol == 0)
		ERROR_EXIT("Symbol debug NULL", __FILE__, NULL, NULL);
	nb_symbol = 0;
	i = 0;
	while (i < end_symbol && (symbol[i].type & N_TYPE) == type)
		i++;
	while (i < end_symbol && (symbol[i].type & N_STAB) == 0 &&
			(symbol[i].type & N_TYPE) != type)
		i++;
	start = (i < end_symbol) ? &symbol[i] : NULL;
	while (i < end_symbol && (symbol[i].type & N_STAB) != 0 &&
			(symbol[i].type & N_TYPE) != type && symbol[i].value == value)
	{
		i++;
		nb_symbol++;
	}
	if (start != NULL && nb_symbol > 0)
		ft_qsort(start, nb_symbol, sizeof(*symbol), sort_ascii);
}

void						sort_type_ascii(t_symbol *symbol, uint32_t type,
		uint32_t end_symbol)
{
	uint32_t				i;
	t_symbol				*start;
	size_t					nb_symbol;

	if (symbol == NULL || end_symbol == 0)
		ERROR_EXIT("Symbol NULL", __FILE__, NULL, NULL);
	nb_symbol = 0;
	i = 0;
	while (i < end_symbol && (symbol[i].type & N_TYPE) != type)
		i++;
	start = (i < end_symbol) ? &symbol[i] : NULL;
	while (i < end_symbol && (symbol[i].type & N_TYPE) == type)
	{
		i++;
		nb_symbol++;
	}
	if (start != NULL && nb_symbol > 0)
		ft_qsort(start, nb_symbol, sizeof(*symbol), sort_ascii);
}