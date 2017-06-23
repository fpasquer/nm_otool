/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 13:23:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/23 15:15:14 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

bool						put_error_file(char const *path_name)
{
	ft_putstr_fd(path_name, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory.\n", STDERR_FILENO);
	return (false);
}

bool						loop_nm(t_nm *nm, char const *path_name) //je dois check si c' ets un dossier
{
	bool					ret;
	char					*p_name_cpy;
	int						fd;
	struct stat				buff;

	if (nm == NULL || path_name == NULL || (ret = true) != true)
		ERROR_EXIT("NM or path_name == NULL", __FILE__, del_nm, nm);
	if (ft_strchr(path_name, '/') != NULL)
		p_name_cpy = ft_strdup(path_name);
	else
		p_name_cpy = ft_strjoin("./", path_name);
	if (p_name_cpy == NULL)
		ERROR_EXIT("p_name_cpy == NULL", __FILE__, del_nm, nm);
	if ((fd = ft_fopen(p_name_cpy, "r")) <= 0 || fstat(fd, &buff) == -1 ||
			(buff.st_mode & S_IFMT) == S_IFDIR)
		ret = put_error_file(path_name);
	ft_memdel((void**)&p_name_cpy);
	close(fd);
	return (true);																//a voir dans l' avancement
	return (ret);
}
