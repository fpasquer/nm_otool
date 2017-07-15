/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 13:23:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/30 11:00:43 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

static bool					put_error_file(char const *path_name)
{
	ft_putstr_fd(path_name, STDERR_FILENO);
	ft_putstr_fd(": No such file or directorys.\n", STDERR_FILENO);
	return (false);
}

static bool					put_error_binaries(char const *path_name)
{
	ft_putstr_fd(path_name, STDERR_FILENO);
	ft_putstr_fd(": The file was not recognized as a valid object file.\n",
			STDERR_FILENO);
	return (false);
}

static void					reset_struct_nm(t_nm **nm)
{
	if (nm == NULL || *nm == NULL)
		ERROR_EXIT("NM == NULL", __FILE__, NULL, NULL);
	if ((*nm)->fd > 0)
	{
		close((*nm)->fd);
		(*nm)->fd = 0;
	}
	(*nm)->end = NULL;
	if ((*nm)->p_name_cpy != NULL)
		ft_memdel((void**)&(*nm)->p_name_cpy);
	if ((*nm)->data != NULL && (*nm)->data != MAP_FAILED &&
			(*nm)->buff.st_size > 0)
		munmap((*nm)->data, (*nm)->buff.st_size);
}

bool						loop_nm(t_nm *nm, char const *path_name)
{
	bool					ret;

	if (nm == NULL || path_name == NULL || (ret = true) == false)
		ERROR_EXIT("NM or path_name == NULL", __FILE__, del_nm, &nm);
	if (ft_strchr(path_name, '/') != NULL)
		nm->p_name_cpy = ft_strdup(path_name);
	else
		nm->p_name_cpy = ft_strjoin("./", path_name);
	if (nm->p_name_cpy == NULL)
		ERROR_EXIT("p_name_cpy == NULL", __FILE__, del_nm, &nm);
	if ((nm->fd = ft_fopen(nm->p_name_cpy, "r")) <= 0 || fstat(nm->fd,
			&nm->buff) == -1 || (nm->buff.st_mode & S_IFMT) == S_IFDIR)
		ret = put_error_file(path_name);
	if (ret == true && (nm->buff.st_mode & S_IXUSR) == 0)
		ret = put_error_binaries(path_name);
	if (ret == true && (nm->data = mmap(NULL, nm->buff.st_size, PROT_READ,
			MAP_PRIVATE, nm->fd, 0)) == MAP_FAILED)
		ERROR_EXIT("DATA NULL", __FILE__, del_nm, &nm);
	nm->end = (char*)(unsigned long long int)nm->data +
			(unsigned long long int)nm->buff.st_size;
	if (ret == true)
		exe_nm(&nm);
	reset_struct_nm(&nm);
	return (true);																//a voir dans l' avancement attention au retour dans le main
	return (ret);
}
