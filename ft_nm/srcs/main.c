/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 08:05:56 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/24 10:00:08 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

int						main(int argc, char **argv)
{
	bool				found;
	int					i;
	int					j;
	t_nm				*nm;

	if ((nm = init_flags((const char **)argv)) == NULL)
		ERROR_EXIT("nm == NULL", __FILE__, NULL, NULL);
																				printf("flag = %d\n", nm->flags);
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
