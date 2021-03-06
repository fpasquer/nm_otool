/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 13:23:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/04 14:57:28 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

#define ULLI unsigned long long int

static bool					put_error_file(char const *path_name)
{
	ft_putstr_fd(path_name, STDERR_FILENO);
	ft_putstr_fd(": No such file or directorys.\n", STDERR_FILENO);
	return (false);
}

bool						put_error_binaries(char const *path_name)
{
	ft_putstr_fd(path_name, STDERR_FILENO);
	ft_putstr_fd(": The file was not recognized as a valid object file.\n",
			STDERR_FILENO);
	return (false);
}

bool						reset_struct_nm(t_nm **nm, void *ptr)
{
	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM == NULL", __FILE__, NULL, NULL);
	if ((*nm)->fd > 0)
	{
		close((*nm)->fd);
		(*nm)->fd = 0;
	}
	(*nm)->fat = false;
	if ((*nm)->p_name_cpy != NULL)
		ft_memdel((void**)&(*nm)->p_name_cpy);
	if (ptr != NULL && ptr != MAP_FAILED &&
			(*nm)->buff.st_size > 0)
		munmap(ptr, (*nm)->buff.st_size);
	return (true);
}

bool						loop_nm(t_nm *nm, char const *path_name)
{
	void					*ptr;
	bool					ret;
	t_symbol				*symbol;

	if (nm == NULL || path_name == NULL || (ret = true) == false)
		ERROR_EXIT("NM or path_name == NULL", __FILE__, del_nm, &nm);
	ptr = MAP_FAILED;
	if (ft_strchr(path_name, '/') != NULL)
		nm->p_name_cpy = ft_strdup(path_name);
	else
		nm->p_name_cpy = ft_strjoin("./", path_name);
	if (nm->p_name_cpy == NULL)
		ERROR_EXIT("p_name_cpy == NULL", __FILE__, del_nm, &nm);
	if ((nm->fd = ft_fopen(nm->p_name_cpy, "r")) <= 0 || fstat(nm->fd,
			&nm->buff) == -1 || (nm->buff.st_mode & S_IFMT) == S_IFDIR)
		ret = put_error_file(path_name);
	if (ret == true && (ptr = mmap(NULL, nm->buff.st_size, PROT_READ
			| PROT_WRITE, MAP_PRIVATE, nm->fd, 0)) == MAP_FAILED)
		ERROR_EXIT("DATA NULL", __FILE__, del_nm, &nm);
	nm->end = (char*)(ULLI)ptr + (ULLI)nm->buff.st_size;
	if (ret == true && (symbol = exe_nm(&nm, path_name, ptr)) != NULL)
		gestion_symbols(&nm, &symbol, path_name, ptr);
	return (reset_struct_nm(&nm, ptr));
}
