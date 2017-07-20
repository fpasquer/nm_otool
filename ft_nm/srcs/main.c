/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 08:05:56 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/20 14:29:00 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

int							main(int argc, char **argv)
{
	bool					found;
	int						i;
	int						j;
	t_nm					*nm;

	if ((nm = init_flags((const char **)argv)) == NULL)
		ERROR_EXIT("nm == NULL", __FILE__, NULL, NULL);
	if (argc <= 1)
		loop_nm(nm, "a.out");
	else if ((i = 0) == 0)
	{
		found = false;
		while (++i < argc && (j = 0) == 0)
		{
			while (ft_isspace(argv[i][j]))
				j++;
			if (argv[i][j] != '-')
				found = loop_nm(nm, &argv[i][j]);
		}
		if (found == false)
			loop_nm(nm, "a.out");
	}
	del_nm(&nm);
	return (EXIT_SUCCESS);
}
