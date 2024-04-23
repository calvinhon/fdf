/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:05:52 by chon              #+#    #+#             */
/*   Updated: 2024/04/05 20:28:28 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_rgb(int rgb, char c)
{
	if (c == 'r')
		return ((rgb >> 16) & 0xFF);
	else if (c == 'g')
		return ((rgb >> 8) & 0xFF);
	else if (c == 'b')
		return (rgb & 0xFF);
	return (0);
}

int	calc_color(double fraction, double color1, double color2)
{
	t_color	c;
	int		beg_color;
	int		end_color;

	if (color1 == 0)
		beg_color = PURPLE;
	else
		beg_color = color1;
	if (color2 == 0)
		end_color = GOLD;
	else
		end_color = color2;
	c.r1 = get_rgb(beg_color, 'r');
	c.g1 = get_rgb(beg_color, 'g');
	c.b1 = get_rgb(beg_color, 'b');
	c.r2 = get_rgb(end_color, 'r');
	c.g2 = get_rgb(end_color, 'g');
	c.b2 = get_rgb(end_color, 'b');
	c.r3 = c.r1 + (c.r2 - c.r1) * fraction;
	c.b3 = c.b1 + (c.b2 - c.b1) * fraction;
	c.g3 = c.g1 + (c.g2 - c.g1) * fraction;
	return (c.r3 << 16 | c.g3 << 8 | c.b3);
}

double	col_fract(t_pt_dets p1, t_pt_dets p2, double dx, double dy)
{
	if (dy > dx)
		return ((p1.y - p2.y) / dy);
	else
		return ((p1.x - p2.x) / dx);
}

void	assign_color(t_pt_dets **map, double min_z, double max_z)
{
	t_ct_vars	a;
	double		range;
	double		fraction;
	double		adj;

	a.i = -1;
	a.j = -1;
	adj = min(2, 0, -min_z);
	range = max_z - min_z;
	while (map[++a.i])
	{
		while (map[a.i][++a.j].end)
		{
			if (range == 0)
				fraction = 0;
			else
				fraction = (map[a.i][a.j].z + adj) / range;
			if (map[a.i][a.j].color == 0)
				map[a.i][a.j].color = calc_color(fraction, 0, 0);
		}
		a.j = -1;
	}
}

void	get_color(t_pt_dets **map)
{
	t_sizing	s;
	t_ct_vars	a;

	a.i = -1;
	a.j = 0;
	s.min_z = map[0][0].z;
	s.max_z = map[0][0].z;
	while (map[++a.i])
	{
		while (map[a.i][a.j].end)
		{
			s.min_z = min(2, map[a.i][a.j].z, s.min_z);
			s.max_z = max(2, map[a.i][a.j++].z, s.max_z);
		}
		a.j = 0;
	}
	assign_color(map, s.min_z, s.max_z);
}
