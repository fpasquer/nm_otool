/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 12:23:18 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/06 12:28:39 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

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

# define NB_FUNC 6u

# define LEN_64_BIT 16u
# define LEN_32_BIT 8u
# define NB_EACH_LINE 16u

# ifdef __x86_64__
#  define CPU_TYPE CPU_TYPE_X86_64
#  define CPU_SUB_TYPE CPU_SUBTYPE_X86_ALL
# endif
# ifdef __i386__
#  define CPU_TYPE CPU_TYPE_I386
#  define CPU_SUB_TYPE CPU_SUBTYPE_X86_64_ALL
# endif

# define B_TO_L(m, v) ((m) ? b_to_l_endian(v) : v)

typedef struct				s_cpu_type_str
{
	uint32_t				key;
	char					*str;
}							t_cpu_type_str;

typedef struct				s_otool
{
	void					*ptr;
	void					*end;
	bool					cigam;
	bool					bits64;
	char					*path_name;
	int						fd;
	bool					fat;
	bool					not_foond;
	uint32_t				cpu_type;
	uint32_t				end_seg;
	struct stat				stat;
}							t_otool;

typedef struct				s_func_struct
{
	uint32_t				key;
	void					*(*func)(t_otool *, char const *, void const *);
}							t_func_struct;

t_func_struct				g_funcs[NB_FUNC];

void						ft_otool(char const *name);
char						*get_path_name(char const *name);
bool						put_error_file(char const *str);
void						*exe_otool(t_otool *otool, char const *name,
		void const *ptr);
void						print_header(char const *name, char const *segname,
		char const *sectname, t_otool *otool);
void						print_value(uint64_t const addr, size_t len,
		uint64_t length);
void						print_line(uint64_t length, void const *ptr,
		t_otool *otool);

uint32_t					b_to_l_endian(uint32_t num);

void						*func_32(t_otool *otool, char const *name,
		void const *ptr);
void						*func_64(t_otool *otool, char const *name,
		void const *ptr);
void						*func_fat(t_otool *otool, char const *name,
		void const *ptr);
void						*func_32_cigam(t_otool *otool, char const *name,
		void const *ptr);
void						*func_64_cigam(t_otool *otool, char const *name,
		void const *ptr);

#endif
