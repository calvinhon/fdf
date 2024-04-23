/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:51:24 by chon              #+#    #+#             */
/*   Updated: 2024/04/05 20:32:45 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cast_image(t_mlx_vars *env)
{
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

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
				1 - fabs(col_fract(p1, p2, b.dx, b.dy)), p1.color, p2.color));
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

t_pt_dets	adjust_pt(t_mlx_vars *env, t_pt_dets pt)
{
	t_pt_dets	new_pt;

	new_pt = pt;
	new_pt = rotate_z(new_pt, env);
	new_pt = rotate_x(new_pt, env);
	new_pt.x *= env->adj.init_zoom_factor;
	new_pt.x += env->adj.init_x_offset;
	new_pt.y *= env->adj.init_zoom_factor;
	new_pt.y += env->adj.init_y_offset;
	return (new_pt);
}

void	create_grid(t_mlx_vars *env, t_pt_dets **map)
{
	t_ct_vars	a;
	t_mult_pts	p;

	a.i = -1;
	a.j = -1;
	ft_bzero(env->addr, 1920 * 1080 * (env->bpp / 8));
	while (map[++a.i])
	{
		while (map[a.i][++a.j].end)
		{
			p.x1 = adjust_pt(env, map[a.i][a.j]);
			if (map[a.i][a.j + 1].end)
			{
				p.x2 = adjust_pt(env, map[a.i][a.j + 1]);
				pixels(env, p.x1, p.x2);
			}
			if (map[a.i + 1])
			{
				p.x3 = adjust_pt(env, map[a.i + 1][a.j]);
				pixels(env, p.x1, p.x3);
			}
		}
		a.j = -1;
	}
	cast_image(env);
}
