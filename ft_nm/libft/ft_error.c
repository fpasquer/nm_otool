/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:49:33 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/23 11:09:50 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_error(const char *s, const char *function,
		void (*f)(void*), void *ptr)
{
	ft_putstr_fd("Error : ", STDERR_FILENO);
	if (s != NULL && s[0] != '\0')
		ft_putendl_fd(s, STDERR_FILENO);
	ft_putendl_fd(function, STDERR_FILENO);
	if (f != NULL && ptr != NULL)
		f(ptr);
}
