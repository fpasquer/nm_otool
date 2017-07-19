/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 16:07:00 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/19 22:47:48 by fpasquer         ###   ########.fr       */
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
	if ((((*nm)->flags) & F_A_MAJ) != 0 || (((*nm)->flags) & F_O_MIN) != 0)
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

static bool					write_symbol(unsigned int flags, t_symbol symbol)
{
	if (!((flags & F_A_MIN) != 0 || (symbol.type & N_STAB) == 0))
		return (false);
	if ((flags & F_G_MIN) != 0 && (symbol.type & N_EXT) != 0)
	{
		if (((symbol.type & N_TYPE) != N_UNDF && (flags & F_U_MIN) == 0) ||
				((symbol.type & N_TYPE) == N_UNDF && (flags & F_U_MAJ) == 0))
			return (true);
	}
	else if ((flags & F_G_MIN) == 0)
	{
		if ((flags & F_U_MIN) != 0 && (symbol.type & N_TYPE) == N_UNDF && (flags & F_U_MAJ) == 0)
			return (true);
		else if ((flags & F_U_MAJ) != 0 && (symbol.type & N_TYPE) != N_UNDF && (flags & F_U_MIN) == 0)
			return (true);
		else if ((flags & F_U_MIN) == 0 && (flags & F_U_MAJ) == 0)
			return (true);
	}
	return (false);
}

void						print_symbols(t_nm const **nm,
		t_symbol const *symbol, char const *name_file)
{
	uint32_t				i;
	uint32_t				decalage;
	uint32_t				end;

	if (!nm || !(*nm) || !symbol || !init_cache_print(STDOUT_FILENO))
		ERROR_EXIT("Invalid values", __FILE__, NULL, NULL);
	i = (((*nm)->flags & F_R_MIN) != 0) ? (*nm)->nb_symbol - 1 : 0;
	decalage = (((*nm)->flags & F_R_MIN) != 0) ? -1 : 1;
	end = (((*nm)->flags & F_R_MIN) != 0) ? 0 + -1 : (*nm)->nb_symbol;
	if ((*nm)->nb_file > 1 && ((*nm)->flags & F_A_MAJ) == 0 &&
			((*nm)->flags & F_O_MIN) == 0)
	{
		add_cache_print("\n");
		add_cache_print(name_file);
		add_cache_print(":\n");
	}
	while (i != end)
	{
		if (write_symbol((*nm)->flags, symbol[i]) == true)
			print_symbol(nm, symbol[i], name_file);
		i += decalage;
	}
	print_cache();
}