/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_desc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:24:32 by fpasquer          #+#    #+#             */
/*   Updated: 2017/07/18 14:25:44 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

#define NB_DESC 18

typedef struct				s_desc
{
	uint16_t				key;
	char					value[100];
}							t_desc;

static t_desc				g_tab_desc[NB_DESC] = 
{
	{N_GSYM, "GSYM"},
	{N_FNAME, "FNAME"},
	{N_FUN, "FUN"},
	{N_STSYM, "STSYM"},
	{N_LCSYM, "LCSYM"},
	{N_BNSYM, "BNSYM"},
	{N_AST, "AST"},
	{N_OPT, "OPT"},
	{N_RSYM, "RSYM"},
	{N_SLINE, "SLINE"},
	{N_ENSYM, "ENSYM"},
	{N_SSYM, "SSYM"},
	{N_SO, "SO"},
	{N_OSO, "OSO"},
	{N_LSYM, "LSYM"},
	{N_BINCL, "BINCL"},
	{N_SOL, "SOL"},
	{N_PARAMS, "PARAMS"}
};

char						*get_desc(t_symbol const symbol)
{
	unsigned int			i;

	i = 0;
	while (i++ < NB_DESC)
		if (symbol.desc == g_tab_desc[i - 1].key)
			return (g_tab_desc[i - 1].value);
	printf("desc = %03x\n", symbol.desc & REFERENCE_TYPE);
	return ("ERROR");
}