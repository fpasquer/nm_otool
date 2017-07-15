/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 08:09:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/15 12:50:48 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h>
# include <stdlib.h> //malloc free
# include <fcntl.h> // open
# include <unistd.h> //close write
# include <stdbool.h>
# include <sys/mman.h> //mmap munmap
# include <sys/stat.h> //fstat
# include "../libft/libft.h"
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

//nm [ -agnoprumxjlfPA [ s segname sectname ]] [ - ] [ -t format ] [[ -arch arch_flag ]...] [ file ... ]
# define F_NONE 0x0u
# define F_A_MIN 0x1u
# define F_G_MIN 0x2u
# define F_N_MIN 0x4u
# define F_O_MIN 0x8u
# define F_P_MIN 0x10u
# define F_R_MIN 0x20u
# define F_U_MIN 0x40u
# define F_M_MIN 0x80u
# define F_X_MIN 0x100u
# define F_L_MIN 0x200u
# define F_F_MIN 0x400u
# define F_P_MAJ 0x800u
# define F_A_MAJ 0x1000u

/*
**	p_name_cpy	:			copy du nom passe en parametre, avec le path
**	data		:			adresse du debut du retour de mmap
**	end			:			pointeur de fin du fichier
**	fd			:			file descriptor du binaire
**	flags		:			options passees en parametre par les argv
**	buff		:			status du binaires
*/

typedef struct				s_symbol
{
	char					*name;
	uint64_t				value;
	uint8_t					type;
}							t_symbol;

typedef struct				s_nm
{
	char					*p_name_cpy;
	char					*data;
	char					*end;
	int						fd;
	unsigned int			flags;
	struct stat				buff;
}							t_nm;

# define NB_FUNC 6

typedef struct				s_func_nm
{
	uint32_t				key;
	bool					(*f)(t_nm const **);
}							t_func_nm;

t_nm						*init_flags(char const **argv);
bool						loop_nm(t_nm *nm, char const *path_name);
void						del_nm(void *nb);
void						print_nm(t_nm *nm);
bool						exe_nm(t_nm **nm);

bool						func_32(t_nm const **nm);
bool						func_32_cigan(t_nm const **nm);
bool						func_64(t_nm const **nm);
bool						func_64_cigan(t_nm const **nm);
bool						error_magic_number(t_nm const **nm);
bool						func_fat_magic(t_nm const **nm);
bool						func_fat_cigam(t_nm const **nm);

#endif
