/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:47:22 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:47:35 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long int		ft_abs(long long int nb)
{
	return ((nb < 0) ? nb * -1 : nb);
}