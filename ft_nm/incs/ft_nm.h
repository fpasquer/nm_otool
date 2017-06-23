/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 08:09:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/23 13:51:59 by fpasquer         ###   ########.fr       */
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

typedef struct				s_nm
{
	unsigned int			flags;
}							t_nm;

t_nm						*init_flags(char const **argv);
bool						loop_nm(t_nm *nm, char const *path_name);
void						del_nm(void *nb);

#endif
