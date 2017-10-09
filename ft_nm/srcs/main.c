/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 08:05:56 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/09 07:14:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

int							main(int argc, char **argv)
{
	int						found;
	int						i;
	int						j;
	t_nm					*nm;

	if (!(nm = init_flags((const char **)argv)) || init_cache_print(1) == false)
		ERROR_INT("nm == NULL", __FILE__, NULL, NULL);
	found = false;
	if (argc <= 1)
		loop_nm(nm, "a.out");
	else if ((i = 0) == 0)
	{
		while (++i < argc && (j = 0) == 0 && found != -1)
		{
			while (ft_isspace(argv[i][j]))
				j++;
			if (argv[i][j] != '-')
				found = loop_nm(nm, &argv[i][j]);
		}
		if (found == false)
			loop_nm(nm, "a.out");
	}
	if (found != -1)
		del_nm(&nm);
	return (found == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}
