/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:59:49 by chon              #+#    #+#             */
/*   Updated: 2024/04/04 18:56:27 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

double	max(int n, ...)
{
	va_list	args;
	double	max_num;
	double	cur;

	va_start(args, n);
	max_num = va_arg(args, double);
	while (n > 1)
	{
		cur = va_arg(args, double);
		if (cur > max_num)
			max_num = cur;
		n--;
	}
	va_end(args);
	return (max_num);
}

double	min(int n, ...)
{
	va_list	args;
	double	min_num;
	double	cur;

	va_start(args, n);
	min_num = va_arg(args, double);
	while (n > 1)
	{
		cur = va_arg(args, double);
		if (cur < min_num)
			min_num = cur;
		n--;
	}
	va_end(args);
	return (min_num);
}

t_pt_dets	rotate_x(t_pt_dets pt, t_mlx_vars *env)
{
	t_pt_dets	new_pt;

	new_pt = pt;
	new_pt.y = pt.y * cos(env->adj.rotate_x) - pt.z * sin(env->adj.rotate_x);
	new_pt.z = pt.y * sin(env->adj.rotate_x) + pt.z * cos(env->adj.rotate_x);
	return (new_pt);
}

t_pt_dets	rotate_z(t_pt_dets pt, t_mlx_vars *env)
{
	t_pt_dets	new_pt;

	new_pt = pt;
	new_pt.x = pt.x * cos(env->adj.rotate_z) - pt.y * sin(env->adj.rotate_z);
	new_pt.y = pt.x * sin(env->adj.rotate_z) + pt.y * cos(env->adj.rotate_z);
	return (new_pt);
}

t_pt_dets	adjust_pt(t_mlx_vars *env, t_pt_dets pt)
{
	t_pt_dets	new_pt;

	new_pt = pt;
	new_pt.z = pt.z * env->adj.height_factor;
	new_pt = rotate_z(new_pt, env);
	new_pt = rotate_x(new_pt, env);
	new_pt.x *= env->adj.init_zoom_factor * env->adj.zoom_factor;
	new_pt.x += env->adj.init_x_offset + env->adj.x_offset;
	new_pt.y *= env->adj.init_zoom_factor * env->adj.zoom_factor;
	new_pt.y += env->adj.init_y_offset + env->adj.y_offset;
	return (new_pt);
}
