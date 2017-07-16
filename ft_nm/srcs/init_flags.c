/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 08:47:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/16 16:23:40 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

static bool					save_each_flag(t_nm **nm, char c_src,
		char c_cmp, int define)
{
	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM == NULL", __FILE__, NULL, NULL);
	if (c_src != c_cmp)
		return (false);
	(*nm)->flags = (*nm)->flags | define;
	return (true);
}

static void					show_error_options(char c)
{
	ft_putstr_fd("Option : ", STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putstr_fd(" unvalable.\n", STDERR_FILENO);
}

static void					save_flags(char const *argv, t_nm *nm)
{
	unsigned int			ret;
	unsigned int			i;

	if (nm == NULL || argv == NULL)
		ERROR_EXIT("FLAG or ARGV == NULL", __FILE__, del_nm, nm);
	i = 0;
	while (argv[i++] != '\0')
	{
		ret = save_each_flag(&nm, argv[i - 1], 'a', F_A_MIN);
		ret += save_each_flag(&nm, argv[i - 1], 'g', F_G_MIN);
		ret += save_each_flag(&nm, argv[i - 1], 'n', F_N_MIN);
		ret += save_each_flag(&nm, argv[i - 1], 'o', F_O_MIN);
		ret += save_each_flag(&nm, argv[i - 1], 'p', F_P_MIN);
		ret += save_each_flag(&nm, argv[i - 1], 'r', F_R_MIN);
		ret += save_each_flag(&nm, argv[i - 1], 'u', F_U_MIN);
		ret += save_each_flag(&nm, argv[i - 1], 'm', F_M_MIN);
		ret += save_each_flag(&nm, argv[i - 1], 'x', F_X_MIN);
		ret += save_each_flag(&nm, argv[i - 1], 'j', F_J_MIN);
		ret += save_each_flag(&nm, argv[i - 1], 'l', F_L_MIN);
		ret += save_each_flag(&nm, argv[i - 1], 'f', F_F_MIN);
		ret += save_each_flag(&nm, argv[i - 1], 'P', F_P_MAJ);
		if ((ret += save_each_flag(&nm, argv[i - 1], 'A', F_A_MAJ)) == 0)
			show_error_options(argv[i - 1]);
	}
}

t_nm						*init_flags(char const **argv)
{
	unsigned int			i;
	unsigned int			j;
	t_nm					*nm;

	if ((nm = (t_nm*)ft_memalloc(sizeof(*nm))) == NULL)
		ERROR_EXIT("Malloc failled", __FILE__, NULL, NULL);
	nm->flags = F_NONE;
	nm->data = MAP_FAILED;														// pour initialuser le pointer de data et empecher le munmap
	i = 0;
	while (argv[i] != NULL)
	{
		j = 0;
		while (ft_isspace(argv[i][j]))
			j++;
		if (argv[i][j] == '-' && argv[i][j + 1] != '\0')
			save_flags(&(argv[i][j + 1]), nm);
		else if (argv[i][j] == '-' && argv[i][j + 1] == '\0')
			show_error_options(argv[i][j]);
		i++;
	}
	return (nm);
}

void						print_nm(t_nm *nm)
{
	if (nm == NULL)
		return ;
	printf("p_name_cpy = %p >%s<\n", nm->p_name_cpy, nm->p_name_cpy);
	printf("data = %p >%s<\n", nm->data, nm->data == MAP_FAILED ? "" : nm->data);
	printf("fd = %d\n", nm->fd);
	printf("flag = %u\n", nm->flags);
	printf("buff = %p\n", &nm->buff);
}
