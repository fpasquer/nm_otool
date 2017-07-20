/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 08:47:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/20 21:18:40 by fpasquer         ###   ########.fr       */
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
	if (define == F_U_MIN)
		(*nm)->flags = (*nm)->flags | F_J_MIN;
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
		ret += save_each_flag(&nm, argv[i - 1], 'U', F_U_MAJ);
		ret += save_each_flag(&nm, argv[i - 1], 'j', F_J_MIN);
		if ((ret += save_each_flag(&nm, argv[i - 1], 'A', F_A_MAJ)) == 0)
			show_error_options(argv[i - 1]);
	}
}

static void					check_flags(t_nm **nm)
{
	if (nm == NULL || *nm == NULL)
		return ;
	if (((*nm)->flags & F_U_MIN) != 0)
		if (((*nm)->flags & F_A_MIN) != 0)
			(*nm)->flags = (*nm)->flags ^ F_A_MIN;
	if (((*nm)->flags & F_P_MIN) != 0)
	{
		if (((*nm)->flags & F_N_MIN) != 0)
			(*nm)->flags = (*nm)->flags ^ F_N_MIN;
		if (((*nm)->flags & F_R_MIN) != 0)
			(*nm)->flags = (*nm)->flags ^ F_R_MIN;
	}
	if (((*nm)->flags & F_O_MIN) != 0 && ((*nm)->flags & F_A_MAJ) != 0)
		ERROR_EXIT("ft_nm: for the -print-name option!", __FILE__, del_nm, nm);
}

t_nm						*init_flags(char const **argv)
{
	unsigned int			i;
	unsigned int			j;
	t_nm					*nm;

	if ((nm = (t_nm*)ft_memalloc(sizeof(*nm))) == NULL)
		ERROR_EXIT("Malloc failled", __FILE__, NULL, NULL);
	nm->flags = F_NONE;
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
		else
			nm->nb_file = i > 0 ? nm->nb_file + 1 : nm->nb_file;
		i++;
	}
	check_flags(&nm);
	return (nm);
}
