/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:41:45 by chon              #+#    #+#             */
/*   Updated: 2024/03/29 17:22:07 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	x_close(mlx_vars *env)
{
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	free(env->adj);
	free(env->mlx);
	free(env);
	exit(0);
	return (0);
}

int	key(int key, mlx_vars *env)
{
	// printf("%i\n", key);
	if (key == 53)
		x_close(env);
	else if (key == 123 | key == 124 | key == 125 | key == 126)
		translation(key, env);
	// else if (key == 13 | key == 0 | key == 1 | key == 2)
	// 	rotate(key, env);
	// else if (key == 27 | key == 24)
	// 	zoom(key, env);
	else
		return (0);
	create_grid(env, env->map);
	return (0);
}

void	set_controls(mlx_vars *env)
{
	mlx_hook(env->win, 2, 0, key, env);
	mlx_hook(env->win, 17, 0, x_close, env);
	mlx_hook(env->win, 4, 0, mouse, env);
}
