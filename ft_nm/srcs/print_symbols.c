/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 16:07:00 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/05 10:29:54 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

#define ADD_PRINT_SPACE(s) add_cache_print(s); add_cache_print(" ");
#define ADD_PRINT_NAME(s) { add_cache_print(s); add_cache_print(": ");}
#define CIGAM (*nm)->magic == MH_CIGAM_64 || (*nm)->magic == MH_CIGAM
#define MAGIC (*nm)->magic == MH_MAGIC_64 || (*nm)->magic == MH_MAGIC

static char					*get_type(t_nm const **nm, t_symbol const symbol,
		void const *ptr)
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
	else if (type == N_SECT && (CIGAM))
		return ((*nm)->magic == MH_CIGAM_64 ? get_symbol_64(symbol,
					ptr) : get_symbol_32_cigam(symbol, ptr));
	else if (type == N_SECT && (MAGIC))
		return ((*nm)->magic == MH_MAGIC_64 ? get_symbol_64(symbol, ptr) :
				get_symbol_32(symbol, ptr));
	else if (type == N_PBUD)
		return (ext == 0 ? "u" : "U");
	else if (type == N_INDR)
		return (ext == 0 ? "i" : "I");
	else if ((symbol.type & N_STAB) != 0)
		return ("-");
	return ("(?)");
}

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
		char const *bin_name, void const *ptr)
{
	char					buff_value[LEN_64_BIT + 1];

	ft_bzero(buff_value, sizeof(char) * (LEN_64_BIT + 1));
	if ((((*nm)->flags) & F_A_MAJ) != 0 || (((*nm)->flags) & F_O_MIN) != 0)
		ADD_PRINT_NAME(bin_name);
	if (((*nm)->flags & F_J_MIN) == 0)
	{
		if (ft_utoa_base_tab(symbol.value, 16, buff_value, LEN_64_BIT) == false)
			ERROR_VOID("Invalid symbol value", __FILE__, NULL, NULL);
		if (symbol.value != 0 || (symbol.type & N_STAB) != 0)
			place_value(buff_value, (*nm)->magic == MH_MAGIC_64 ? LEN_64_BIT :
					LEN_32_BIT);
		else
			ft_memset(buff_value, (symbol.type & N_TYPE) == N_UNDF ? ' ' : '0',
					sizeof(char) * ((*nm)->magic == MH_MAGIC_64 ? LEN_64_BIT :
					LEN_32_BIT));
		ADD_PRINT_SPACE(buff_value);
		ADD_PRINT_SPACE(get_type(nm, symbol, ptr));
		if (((*nm)->flags & F_A_MIN) != 0)
		{
			ADD_PRINT_SPACE(get_desc(symbol));
		}
	}
	add_cache_print(symbol.name);
	add_cache_print("\n");
}

static bool					write_symbol(unsigned int const f,
		t_symbol const s)
{
	if (!((f & F_A_MIN) != 0 || (s.type & N_STAB) == 0))
		return (false);
	if ((f & F_G_MIN) != 0 && (s.type & N_EXT) != 0)
	{
		if (((s.type & N_TYPE) != N_UNDF && (f & F_U_MIN) == 0) || ((s.type &
				N_TYPE) == N_UNDF && ((s.value == 0 && (f & F_U_MAJ) == 0) ||
				(s.value != 0 && ((f & F_U_MAJ) != 0 || (f & F_U_MIN) == 0)))))
			return ((f & F_U_MIN) != 0 && (f & F_U_MAJ) != 0 ? false : true);
	}
	else if ((f & F_G_MIN) == 0)
	{
		if ((f & F_U_MIN) != 0 && (s.type & N_TYPE) == N_UNDF && s.value ==
				0 && (f & F_U_MAJ) == 0)
			return (true);
		else if ((f & F_U_MAJ) != 0 && ((s.type & N_TYPE) != N_UNDF || (f &
				F_N_MIN) != 0 || ((s.type & N_TYPE) == N_UNDF && s.value != 0))
				&& (f & F_U_MIN) == 0)
			return ((s.value || (s.type & N_TYPE) != N_UNDF) ? true : false);
		else if ((f & F_U_MIN) == 0 && (f & F_U_MAJ) == 0)
			return (true);
	}
	return (false);
}

void						print_symbols(t_nm const **nm,
		t_symbol const *symbol, char const *name_file, void const *ptr)
{
	uint32_t				i;
	uint32_t				decalage;
	uint32_t				end;

	if (!nm || !(*nm) || !symbol)
		ERROR_VOID("Invalid values", __FILE__, NULL, NULL);
	i = (((*nm)->flags & F_R_MIN) != 0) ? (*nm)->nb_symbol - 1 : 0;
	decalage = (((*nm)->flags & F_R_MIN) != 0) ? -1 : 1;
	end = (((*nm)->flags & F_R_MIN) != 0) ? 0 + -1 : (*nm)->nb_symbol;
	if ((*nm)->nb_file > 1 && ((*nm)->flags & F_A_MAJ) == 0 &&
			((*nm)->flags & F_O_MIN) == 0 && (*nm)->fat == false)
	{
		add_cache_print("\n");
		add_cache_print(name_file);
		add_cache_print(":\n");
	}
	while (i != end)
	{
		if (write_symbol((*nm)->flags, symbol[i]) == true)
			print_symbol(nm, symbol[i], name_file, ptr);
		i += decalage;
	}
}
