/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:51:24 by chon              #+#    #+#             */
/*   Updated: 2024/04/04 19:03:52 by chon             ###   ########.fr       */
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

void	init_sizing(t_mlx_vars *env)
{
	t_ct_vars	a;
	t_sizing	s;

	a.i = -1;
	a.j = 0;
	s.max_x = env->map[0][0].x;
	s.max_y = env->map[0][0].y;
	while (env->map[++a.i])
	{
		while (env->map[a.i][a.j].end)
		{
			s.max_x = max(2, env->map[a.i][a.j].x, s.max_x);
			s.max_y = max(2, env->map[a.i][a.j++].y, s.max_y);
		}
		a.j = 0;
	}
	env->adj.init_x_offset = 500;
	env->adj.init_y_offset = 300;
	env->adj.init_zoom_factor = factor_calc(s.max_x, s.max_y);
}

void	create_grid(t_mlx_vars *env, t_pt_dets **map)
{
	t_ct_vars	a;
	t_pt_dets	p1;
	t_pt_dets	p2;
	t_pt_dets	p3;

	a.i = -1;
	a.j = -1;
	ft_bzero(env->addr, 1920 * 1080 * (env->bpp / 8));
	while (map[++a.i])
	{
		while (map[a.i][++a.j].end)
		{
			p1 = adjust_pt(env, map[a.i][a.j]);
			if (map[a.i][a.j + 1].end)
			{
				p2 = adjust_pt(env, map[a.i][a.j + 1]);
				pixels(env, p1, p2);
			}
			if (map[a.i + 1])
			{
				p3 = adjust_pt(env, map[a.i + 1][a.j]);
				pixels(env, p1, p3);
			}
		}
		a.j = -1;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	fdf_legend(env);
}
