/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:51:24 by chon              #+#    #+#             */
/*   Updated: 2024/04/03 19:50:36 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	plot(t_mlx_vars *env, int x, int y, int color)
{
	char	*dst;

	if (x > 1919 || y > 1079 || x < 0 || y < 0)
		return ;
	dst = env->addr + x * env->bpp / 8 + y * env->l_len;
	*(unsigned int *)dst = color;
}

void	pixels(t_mlx_vars *env, t_pt_dets p1, t_pt_dets p2)
{
	t_line	b;

	b.xi = 1;
	b.yi = 1;
	b.dx = roundf(fabs(p2.x - p1.x));
	b.dy = roundf(fabs(p2.y - p1.y));
	increment(p1, p2, &b.xi, &b.yi);
	b.err = b.dx - b.dy;
	while (roundf(fabs(p1.x - p2.x)) > 0 || roundf(fabs(p1.y - p2.y)) > 0)
	{
		plot(env, p1.x, p1.y, calc_color(
				1 - fabs(fraction(p1, p2, b.dx, b.dy)), p1.color, p2.color));
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
	plot(env, p1.x, p1.y, p2.color);
}

void	adjust_grid(t_pt_dets **map)
{
	t_ct_vars	a;
	t_sizing	s;

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

void	rotate_map(double **r_matrix, t_mlx_vars *env)
{
	double		**map_matrix;
	t_ct_vars	a;

	a.i = 0;
	a.j = 0;
	map_matrix = init_matrix(3, 1);
	while (env->map[a.i])
	{
		while (env->map[a.i][a.j].end)
		{
			map_matrix[0][0] = env->map[a.i][a.j].x;
			map_matrix[1][0] = env->map[a.i][a.j].y;
			map_matrix[2][0] = env->map[a.i][a.j].z;
			map_matrix = mult_matrix(3, 1, r_matrix, map_matrix);
			env->map[a.i][a.j].x = map_matrix[0][0];
			env->map[a.i][a.j].y = map_matrix[1][0];
			env->map[a.i][a.j].z = map_matrix[2][0];
			a.j++;
		}
		a.j = 0;
		a.i++;
	}
	free_db_array(map_matrix, 3);
	free_db_array(r_matrix, 3);
}

void	create_grid(t_mlx_vars *env, t_pt_dets **map)
{
	t_ct_vars	a;

	a.i = -1;
	a.j = -1;
	ft_bzero(env->addr, 1920 * 1080 * (env->bpp / 8));
	stretch_transl(map, env->adj.zoom_factor,
		env->adj.x_offset, env->adj.y_offset);
	// printf("r_z:%f r_x:%f\n", env->adj.rotate_z, env->adj.rotate_x);
	// printf("off_x:%d off_y:%d\n", env->adj.x_offset, env->adj.y_offset);
	rotate_map(z_r(init_matrix(3, 3), env->adj.rotate_z), env);
	rotate_map(x_r(init_matrix(3, 3), env->adj.rotate_x), env);
	while (map[++a.i])
	{
		while (map[a.i][++a.j + 1].end)
		{
			pixels(env, map[a.i][a.j], map[a.i][a.j + 1]);
			if (map[a.i + 1])
				pixels(env, map[a.i][a.j], map[a.i + 1][a.j]);
		}
		if (map[a.i + 1])
			pixels(env, map[a.i][a.j], map[a.i + 1][a.j]);
		a.j = -1;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	fdf_legend(env);
	reset_transformation(env);
}
