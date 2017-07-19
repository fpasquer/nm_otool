/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 16:07:00 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/19 19:19:19 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

#define ADD_PRINT_SPACE(s) add_cache_print(s); add_cache_print(" ");
#define ADD_PRINT_NAME(s) { add_cache_print(s); add_cache_print(": ");}

static void					place_value(char *buff, size_t max)
{
	size_t					len;

	if (buff == NULL || max <= 0)
		return ;
	len = ft_strlen(buff);
	while (len-- > 0)
		buff[--max] = buff[len];
	while (max-- > 0)
		buff[max] = '0';
}

static void					print_symbol(t_nm const **nm, t_symbol const symbol,
		char const *bin_name)
{
	char					buff_value[LEN_64_BIT + 1];

	ft_bzero(buff_value, sizeof(char) * (LEN_64_BIT + 1));
	if ((((*nm)->flags) & F_A_MAJ) != 0)
		ADD_PRINT_NAME(bin_name);
	if (((*nm)->flags & F_J_MIN) == 0)
	{
		if(ft_utoa_base_tab(symbol.value, 16, buff_value, LEN_64_BIT) == false)
			ERROR_EXIT("Invalid symbol value", __FILE__, NULL, NULL);
		if (symbol.value != 0 || (symbol.type & N_STAB) != 0)
			place_value(buff_value, (*nm)->magic == MH_MAGIC_64 ? LEN_64_BIT :
					LEN_32_BIT);
		else
			ft_memset(buff_value, (symbol.type & N_TYPE) == N_UNDF ? ' ' : '0',
					sizeof(char) * ((*nm)->magic == MH_MAGIC_64 ? LEN_64_BIT :
					LEN_32_BIT));
		ADD_PRINT_SPACE(buff_value);
		ADD_PRINT_SPACE(get_type(nm, symbol));
		if (((*nm)->flags & F_A_MIN) != 0)
		{
			ADD_PRINT_SPACE(get_desc(symbol));
		}
	}
	add_cache_print(symbol.name);
	add_cache_print("\n");
}

static bool					print_multi_file(t_nm const **nm,
	char const *name_file)
{
	if (nm == NULL || *nm == NULL)
		return (false);
	if ((*nm)->nb_file > 1 && ((*nm)->flags & F_A_MAJ) == 0)
	{
		add_cache_print("\n");
		add_cache_print(name_file);
		add_cache_print(":\n");
	}
	return (true);
}

static bool					init_print_value(uint32_t *i, uint32_t *decalage,
		uint32_t *end, t_nm const **nm)
{
	if (i == NULL || decalage == NULL || end == NULL || nm == NULL)
		return (false);
	if (((*nm)->flags & F_R_MIN) != 0)
	{
		*i = (*nm)->nb_symbol - 1;
		*decalage = -1;
		*end = 0 + -1;
	}
	else
	{
		*i = 0;
		*decalage = 1;
		*end = (*nm)->nb_symbol;
	}
	return (true);
}

void						print_symbols(t_nm const **nm,
		t_symbol const *symbol, char const *name_file)
{
	uint32_t				i;
	uint32_t				decalage;
	uint32_t				end;

	if (nm == NULL || *nm == NULL || symbol == NULL ||
			!init_cache_print(STDOUT_FILENO) || init_print_value(&i, &decalage,
			&end, nm) == false || !print_multi_file(nm, name_file))
		ERROR_EXIT("Invalid values", __FILE__, NULL, NULL);
	while (i != end)
	{
		if (((*nm)->flags & F_A_MIN) != 0 || ((symbol[i]).type & N_STAB) == 0)
		{
			if (((*nm)->flags & F_U_MIN) != 0 && ((symbol[i]).type & N_TYPE) ==
					N_UNDF && ((*nm)->flags & F_U_MAJ) == 0)
				print_symbol(nm, symbol[i], name_file);
			else if (((*nm)->flags & F_U_MAJ) != 0 && ((symbol[i]).type &
					N_TYPE) != N_UNDF && ((*nm)->flags & F_U_MIN) == 0)
				print_symbol(nm, symbol[i], name_file);
			else if (((*nm)->flags & F_U_MIN) == 0 && ((*nm)->flags & F_U_MAJ)
					== 0)
				print_symbol(nm, symbol[i], name_file);
		}
		i += decalage;
	}
	print_cache();
}