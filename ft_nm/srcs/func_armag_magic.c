/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_armag_magic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 21:00:53 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/09 11:57:01 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

#define E ft_memdel((void**)&symbol); print_cache();
#define P add_cache_print("\n"); add_cache_print(name); add_cache_print(":\n");

static bool					get_length_arch(char const *ar_name,
		size_t *v)
{
	char					*start;

	if (v == NULL || ar_name == NULL)
		return (false);
	if ((start = ft_strstr(ar_name, AR_EFMT1)) == NULL)
	{
		*v = 0;
		return (true);
	}
	start += ft_strlen(AR_EFMT1);
	if (start == 0)
		return (false);
	*v = ft_atoi(start);
	return (true);
}

static char					*get_name_symbol(void const *ptr, size_t *length)
{
	struct ar_hdr			*arch;

	if (length == NULL || (arch = (struct ar_hdr*)ptr) == NULL ||
			get_length_arch(arch->ar_name, length) == false)
		return ("ERROR");
	if ((*length) == 0)
	{
		*length = 16;
		return ((char *)ptr);
	}
	return ((char*)ptr + sizeof(struct ar_hdr));
}

static int					print_arch_symbol(t_nm **nm, char const *name_lib,
		char const *name_obj, void *ptr)
{
	int						ret;
	char					*name;
	t_symbol				*sym;

	if (nm == NULL || name_lib == NULL || ptr == NULL || (ret = -1) != -1)
		ERROR_INT("NM = NULL", __FILE__, NULL, NULL);
	if (((*nm)->flags & F_A_MAJ) == 0 && ((*nm)->flags & F_O_MIN) == 0)
	{
		if ((name = ft_multijoin(4, name_lib, "(", name_obj, ")")) == NULL)
			ERROR_INT("NAME_CPY failled", __FILE__, del_nm, nm);
		P;
	}
	else
	{
		if ((name = ft_multijoin(3, name_lib, ":", name_obj)) == NULL)
			ERROR_INT("NAME_CPY failled 2", __FILE__, del_nm, nm);
	}
	if ((sym = exe_nm(nm, name, ptr)) != NULL)
	{
		gestion_symbols(nm, &sym, name, ptr);
		reset_struct_nm(nm, ptr);
		ret = true;
	}
	ft_memdel((void**)&name);
	return (ret);
}

static t_symbol				*save_sort_prit_symbol(t_nm **nm, void *ptr,
		char const *name_lib, unsigned int nb_sym)
{
	int						ret;
	unsigned int			i;
	struct ranlib			*symbol;
	struct ranlib			*tmp;
	size_t					l;

	if (nm == NULL || *nm == NULL || ptr == NULL || nb_sym <= 0 || name_lib ==
			NULL || !(symbol = ft_memalloc(sizeof(struct ranlib) * nb_sym)))
		ERROR_EXIT("NM = NULL 2*", __FILE__, NULL, NULL);
	i = 0;
	while (i++ < nb_sym && (ret = true) == true)
	{
		if ((void*)(tmp = (ptr + (*nm)->size_mem + sizeof(int) + (i - 1) *
				sizeof(*symbol))) + sizeof(*tmp) > (void*)(*nm)->end)
			ERROR_EXIT("Ptr tmp over the end", __FILE__, del_nm, nm);
		symbol[i - 1] = *(struct ranlib*)tmp;
	}
	ft_qsort(symbol, nb_sym, sizeof(*symbol), sort_lib_desc);
	while (--i > 0 && ret == true)
		if (i == nb_sym || symbol[i - 1].ran_off != symbol[i].ran_off)
			ret = print_arch_symbol(nm, name_lib, get_name_symbol(ptr +
					symbol[i - 1].ran_off - SARMAG, &l), ptr +
					symbol[i - 1].ran_off - SARMAG + l + sizeof(struct ar_hdr));
	E;
	return (NULL);
}

t_symbol					*func_armag_magic(t_nm **nm, void *ptr,
		char const *name_bin)
{
	char					*n;
	unsigned int			i;
	size_t					l;
	struct ranlib			*lib;
	struct ar_hdr			*arch;

	if (nm == NULL || *nm == NULL || ptr == NULL || name_bin == NULL)
		ERROR_EXIT("NM = NULL", __FILE__, NULL, NULL);
	if ((size_t)(*nm)->buff.st_size <= sizeof(struct ar_hdr))
		return (NULL);
	arch = (void*)ptr;
	if ((void*)(n = (void*)arch + sizeof(*arch)) >= (void*)(*nm)->end)
		ERROR_EXIT("Ptr name over the end", __FILE__, del_nm, nm);
	if (get_length_arch(arch->ar_name, &l) == false)
		ERROR_EXIT("l not save", __FILE__, del_nm, nm);
	if (ft_strncmp(n, SYMDEF, l) != 0 && ft_strncmp(n, SYMDEF_SORTED, l) != 0)
		ERROR_EXIT("Arch error", __FILE__, del_nm, nm);
	if ((void*)(lib = (void*)arch + sizeof(*arch) + l) + sizeof(*lib) >=
			(void*)(*nm)->end)
		ERROR_EXIT("Ptr lib over the end", __FILE__, del_nm, nm);
	i = *(unsigned int *)(ptr + ((void*)lib - (void*)ptr)) / sizeof(*lib);
	(*nm)->size_mem = ((void*)lib) - ((void*)ptr);
	return (save_sort_prit_symbol(nm, ptr, name_bin, i));
}
