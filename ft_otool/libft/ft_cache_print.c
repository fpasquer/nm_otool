/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cache_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 09:38:58 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/05 15:23:32 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define SIZE_CACHE			10000

static char					g_cache[SIZE_CACHE];
static int					g_fd;
static ssize_t				g_i;

bool						init_cache_print(int const fd)
{
	g_fd = fd;
	g_i = 0;
	ft_bzero(g_cache, sizeof(g_cache));
	return (true);
}

bool						print_cache(void)
{
	bool					ret;

	ret = true;
	if (write(g_fd, g_cache, g_i) != g_i)
		ret = false;
	g_i = 0;
	ft_bzero(g_cache, sizeof(g_cache));
	return (ret);
}

bool						add_cache_print(char const *str)
{
	bool					ret;
	size_t					len;
	size_t					i;

	if ((len = ft_strlen(str)) <= 0)
		return (false);
	i = 0;
	ret = true;
	while (i < len && g_i < SIZE_CACHE)
		g_cache[g_i++] = str[i++];
	if (i < len)
	{
		if (print_cache() == false)
			ret = false;
		add_cache_print(&str[i]);
	}
	return (ret);
}
