/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:05:52 by chon              #+#    #+#             */
/*   Updated: 2024/03/13 19:42:32 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 18 | g << 8 | b);
}

int	get_color_inputs(int trgb, char c)
{
	if (c == 't')
		return ((trgb >> 24) & 0xFF);
	else if (c == 'r')
		return ((trgb >> 16) & 0xFF);
	else if (c == 'g')
		return ((trgb >> 8) & 0xFF);
	else if (c == 'b')
		return (trgb & 0xFF);
	return (0);
}

int	add_shade(int trgb, double shade)
{
	return ((int)shade * 0xFF000000 | trgb);
}
