/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 10:26:41 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/24 11:57:12 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

char						*get_path_name(char const *name)
{
	if (name == NULL)
		return (NULL);
	if (ft_strchr(name, '/') == NULL)
		return (ft_strjoin("./", name));
	return (ft_strdup(name));
}

bool						put_error_file(char const *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	return (false);
}

uint32_t					b_to_l_endian(uint32_t num)
{
	return (((num >> 24) & 0xff) |
			((num << 8) & 0xff0000) |
			((num>>8) & 0xff00) |
			((num<<24) & 0xff000000));
}