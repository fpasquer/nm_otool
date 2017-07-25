/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 10:16:25 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/25 15:13:35 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

static int					init_stat_otool(t_otool *otool)
{
	if (otool == NULL || (otool->fd = ft_fopen(otool->path_name, "r")) <= 0)
		return (put_error_file("otool NULL or path invalable"));
	if (fstat(otool->fd, &otool->stat) == -1 ||
			(otool->stat.st_mode & S_IFMT) == S_IFDIR)
		return (put_error_file("Is a directory"));
	if ((otool->ptr = mmap(NULL, otool->stat.st_size, PROT_READ, MAP_PRIVATE,
			otool->fd, 0)) == MAP_FAILED)
		return (put_error_file("MMAP failled"));
	otool->end = (void*)otool->ptr + otool->stat.st_size;
	return (true);
}

static void					del_otool(t_otool *otool)
{
	if (otool == NULL)
		return ;
	if (otool->path_name != NULL)
		ft_memdel((void**)&otool->path_name);
	if (otool->fd > 0)
		close(otool->fd);
	if (otool->ptr != MAP_FAILED)
		munmap(otool->ptr, otool->end - otool->ptr);
}

void						ft_otool(char const *name)
{
	t_otool					otool;

	ft_bzero(&otool, sizeof(otool));
	if (name == NULL || (otool.path_name = get_path_name(name)) == NULL)
		return ;
	otool.ptr = MAP_FAILED;
	if (init_stat_otool(&otool) == true)
		exe_otool(otool, name, otool.ptr);
	del_otool(&otool);
}