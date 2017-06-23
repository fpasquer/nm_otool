/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 08:05:56 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/23 11:34:22 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

int						main(int argc, char **argv)
{
	t_nm				*nm;

	argc = 0;
	if ((nm = init_flags((const char **)argv)) == NULL)
		ERROR_EXIT("nm == NULL", __FILE__, NULL, NULL);
	printf("flag = %d\n", nm->flags);
	del_nm(&nm);
	return (EXIT_SUCCESS);
}
