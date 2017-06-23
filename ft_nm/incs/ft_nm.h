/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 08:09:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/23 11:03:50 by fpasquer         ###   ########.fr       */
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
# define F_NONE 0x0
# define F_A_MIN 0x1
# define F_G_MIN 0x2
# define F_N_MIN 0x4
# define F_O_MIN 0x8
# define F_P_MIN 0x10
# define F_R_MIN 0x20
# define F_U_MIN 0x40
# define F_M_MIN 0x80
# define F_X_MIN 0x100
# define F_L_MIN 0x200
# define F_F_MIN 0x400
# define F_P_MAJ 0x800
# define F_A_MAJ 0x1000

typedef struct				s_nm
{
	unsigned int			flags;
}							t_nm;

t_nm						*init_flags(char const **argv);
void						del_nm(void *nb);

#endif
