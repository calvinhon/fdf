/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:51:24 by chon              #+#    #+#             */
/*   Updated: 2024/03/27 15:09:13 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	plot(mlx_vars *env, int x, int y, int color)
{
	// char	*dst;
	int	i;

	// printf("%d,%d\n", x, y);
	if (x > 1919 || y > 1079 || x < 0 || y < 0)
		return ;
	// dst = env->addr + y * env->l_len + x * env->bpp / 8;
	// *(unsigned int *)dst = color;
	// i = x * env->bpp / 8 + y * env->l_len;
	i = x + y;
	(void)color;
	(void)env;
	// printf("ok\n");
	// env->addr[i] = color;
	// env->addr = *(unsigned int *)color;
}

void	pixels(mlx_vars *env, pt_dets p1, pt_dets p2)
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
		plot(env->img, p1.x, p1.y, p1.color);
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
	plot(env->img, p1.x, p1.y, p1.color);
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

void	create_grid(mlx_vars *env, pt_dets **map)
{
	ct_vars	a;

	a.i = -1;
	a.j = -1;
	rotate_map(z_r(init_matrix(3, 3), M_PI / 4), map);
	rotate_map(x_r(init_matrix(3, 3), atan(sqrt(2))), map);
	adjust_grid(map);
	// printf("%d\n", env->adj->x_offset);
	stretch_transl(map, 1, 50 + env->adj->x_offset, 50);
	while (map[++a.i])
	{
		while (map[a.i][++a.j + 1].end)
		{
			pixels(env->img, map[a.i][a.j], map[a.i][a.j + 1]);
			if (map[a.i + 1])
				pixels(env->img, map[a.i][a.j], map[a.i + 1][a.j]);
		}
		if (map[a.i + 1])
			pixels(env->img, map[a.i][a.j], map[a.i + 1][a.j]);
		a.j = -1;
	}
}
