/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 10:09:23 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/05 14:25:38 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

int							main(int argc, char **argv)
{
	int						i;

	if (argc <= 1)
		ft_putstr_fd("ft_otool <object file>\n", STDERR_FILENO);
	else
	{
		init_cache_print(STDOUT_FILENO);
		i = 1;
		while (argv[i] != NULL)
			ft_otool(argv[i++]);
		print_cache();
	}
	return (EXIT_SUCCESS);
}
