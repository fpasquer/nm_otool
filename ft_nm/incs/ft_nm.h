/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 08:09:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/22 16:31:11 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/stab.h>
# include <mach/machine.h>
# include <ar.h>
# include <mach-o/ranlib.h>

#ifdef __x86_64__
	# define CPU_TYPE CPU_TYPE_X86_64
	# define CPU_SUB_TYPE CPU_SUBTYPE_X86_ALL
#endif
#ifdef __i386__
	# define CPU_TYPE CPU_TYPE_I386
	# define CPU_SUB_TYPE CPU_SUBTYPE_X86_64_ALL
#endif

/*
** -j -n -u -p -U -r -A -g -o
*/

# define F_NONE 0x0u
# define F_A_MIN 0x1u
# define F_G_MIN 0x2u
# define F_N_MIN 0x4u
# define F_O_MIN 0x8u
# define F_P_MIN 0x10u
# define F_R_MIN 0x20u
# define F_U_MIN 0x40u
# define F_U_MAJ 0x80u
# define F_J_MIN 0x100u
# define F_A_MAJ 0x200u

# define LEN_64_BIT 16u
# define LEN_32_BIT 8u

typedef struct				s_symbol
{
	char					*name;
	uint64_t				value;
	uint8_t					type;
	uint8_t					sect;
	uint16_t				desc;
}							t_symbol;

/*
**	p_name_cpy	:			copy du nom passe en parametre, avec le path
**	data		:			adresse du debut du retour de mmap
**	end			:			pointeur de fin du fichier
**	fd			:			file descriptor du binaire
**	nb_symbol	:			nombre de symbole trouvé;
**	flags		:			options passees en parametre par les argv
**	buff		:			status du binaires
*/

typedef struct				s_nm
{
	bool					fat;
	char					*p_name_cpy;
	char					*end;
	int						fd;
	uint32_t				nb_symbol;
	uint32_t				magic;
	unsigned int			nb_file;
	unsigned int			flags;
	size_t					len_addr;
	size_t					size_mem;
	struct stat				buff;
}							t_nm;

# define NB_FUNC 6

typedef struct				s_func_nm
{
	uint32_t				key;
	t_symbol				*(*f)(t_nm **, void *, char const *);
}							t_func_nm;

t_func_nm					g_func[NB_FUNC];

t_nm						*init_flags(char const **argv);
bool						loop_nm(t_nm *nm, char const *path_name);
void						del_nm(void *nb);
void						print_nm(t_nm *nm);
t_symbol					*exe_nm(t_nm **nm, char const *name_bin, void *ptr);
void						gestion_symbols(t_nm **nm, t_symbol **symbol,
		char const *name_file, void const *ptr);

t_symbol					*func_32(t_nm **nm, void *ptr, char const *name_bin);
t_symbol					*func_32_cigam(t_nm **nm, void *ptr, char const *name_bin);
t_symbol					*func_64(t_nm **nm, void *ptr, char const *name_bin);
t_symbol					*func_64_cigam(t_nm **nm, void *ptr, char const *name_bin);
t_symbol					*error_magic_number(t_nm **nm, void *ptr, char const *name_bin);
t_symbol					*func_fat_magic(t_nm **nm, void *ptr, char const *name_bin);
t_symbol					*func_fat_cigam(t_nm **nm, void *ptr, char const *name_bin);
t_symbol					*func_armag_magic(t_nm **nm, void *ptr,char const *name_bin);

int							sort_ascii(const void *, const void *);
int							sort_numerically(void const *a, void const *b);
int							sort_lib_desc(void const *a, void const *b);
void						sort_type_ascii(t_symbol *symbol, uint32_t type,
		uint32_t end_symbol);
void						sort_type_ascii_debug(t_symbol *symbol,
		uint32_t type, uint32_t end_symbol, uint64_t value);

void						print_symbols(t_nm const **nm,
		t_symbol const *symbol, char const *name_file, void const *ptr);
char						*get_symbol_64(t_symbol const symbol,
		void const *ptr);
char						*get_symbol_32(t_symbol const symbol,
		void const *ptr);
char						*get_desc(t_symbol const symbol);
bool						put_error_binaries(char const *path_name);
bool						reset_struct_nm(t_nm **nm, void *ptr);
uint32_t					b_to_l_endian(uint32_t num);

#endif
