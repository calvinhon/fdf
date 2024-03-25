/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:51:24 by chon              #+#    #+#             */
/*   Updated: 2024/03/25 16:56:26 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	plot(t_data *data, int x, int y, int color)
{
	char	*dst;

	// printf("%d,%d\n", x, y);
	if (x > 1919 || y > 1079 || x < 0 || y < 0)
		return ;
	dst = data->addr + y * data->l_len + x * (data->bpp / 8);
	*(unsigned int *)dst = color;
}

void	pixels(t_data img, pt_dets p1, pt_dets p2)
{
	line	b;

	b.xi = 1;
	b.yi = 1;
	b.dx = roundf(fabs(p2.x - p1.x));
	b.dy = roundf(fabs(p2.y - p1.y));
	increment(p1, p2, &b.xi, &b.yi);
	b.err = b.dx - b.dy;
	while (roundf(fabs(p1.x - p2.x)) > 0 || roundf(fabs(p1.y - p2.y)) > 0)
	{
		plot(&img, p1.x, p1.y, p1.color);
		b.err2 = 2 * b.err;
		if (b.err2 > -b.dy)
		{
			b.err -= b.dy;
			p1.x += b.xi;
		}
		if (b.err2 < b.dx)
		{
			b.err += b.dx;
			p1.y += b.yi;
		}
	}
	plot(&img, p1.x, p1.y, p1.color);
}

void	adjust_grid(pt_dets **map)
{
	ct_vars		a;
	sizing		s;

	a.i = -1;
	a.j = 0;
	s.min_x = map[0][0].x;
	s.max_x = map[0][0].x;
	s.min_y = map[0][0].y;
	s.max_y = map[0][0].y;
	while (map[++a.i])
	{
		while (map[a.i][a.j].end)
		{
			s.min_x = min(2, map[a.i][a.j].x, s.min_x);
			s.max_x = max(2, map[a.i][a.j].x, s.max_x);
			s.min_y = min(2, map[a.i][a.j].y, s.min_y);
			s.max_y = max(2, map[a.i][a.j++].y, s.max_y);
		}
		a.j = 0;
	}
	s.max_x -= min(2, 0, s.min_x);
	s.max_y -= min(2, 0, s.min_y);
	stretch_transl(map, 1, max(2, -s.min_x, 0), max(2, -s.min_y, 0));
	stretch_transl(map, factor_calc(s.max_x, s.max_y), 0, 0);
}

void	rotate_map(double **r_matrix, pt_dets **map)
{
	double	**map_matrix;
	ct_vars	a;

	a.i = 0;
	a.j = 0;
	map_matrix = init_matrix(3, 1);
	while (map[a.i])
	{
		while (map[a.i][a.j].end)
		{
			map_matrix[0][0] = map[a.i][a.j].x;
			map_matrix[1][0] = map[a.i][a.j].y;
			map_matrix[2][0] = map[a.i][a.j].z;
			map_matrix = mult_matrix(3, 1, r_matrix, map_matrix);
			map[a.i][a.j].x = map_matrix[0][0];
			map[a.i][a.j].y = map_matrix[1][0];
			map[a.i][a.j].z = map_matrix[2][0] * 1;
			a.j++;
		}
		a.j = 0;
		a.i++;
	}
	free_db_array(map_matrix, 3);
	free_db_array(r_matrix, 3);
}

void	create_grid(mlx_vars *vars, t_data img, pt_dets **map)
{
	ct_vars	a;

	a.i = -1;
	a.j = -1;
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_len, &img.endian);
	rotate_map(z_r(init_matrix(3, 3), M_PI / 4), map);
	rotate_map(x_r(init_matrix(3, 3), atan(sqrt(2))), map);
	adjust_grid(map);
	vars->adj->x_offset = 0;
	// printf("%d\n", vars->adj->x_offset);
	stretch_transl(map, 1, 100 + vars->adj->x_offset, 50);
	while (map[++a.i])
	{
		while (map[a.i][++a.j + 1].end)
		{
			pixels(img, map[a.i][a.j], map[a.i][a.j + 1]);
			if (map[a.i + 1])
				pixels(img, map[a.i][a.j], map[a.i + 1][a.j]);
		}
		if (map[a.i + 1])
			pixels(img, map[a.i][a.j], map[a.i + 1][a.j]);
		a.j = -1;
	}
}
