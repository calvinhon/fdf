/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:19:04 by chon              #+#    #+#             */
/*   Updated: 2024/04/02 17:33:04 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	fdf_legend(mlx_vars *env)
{
	void	*mlx;
	void	*win;

	mlx = env->mlx;
	win = env->win;
	mlx_string_put(mlx, win, 30, 30, LIME, "CONTROLS LEGEND");
	mlx_string_put(mlx, win, 30, 50, WHITE, "Arrow Keys: Translate");
	mlx_string_put(mlx, win, 30, 70, WHITE, "WASD: Rotate");
	mlx_string_put(mlx, win, 30, 90, WHITE, "Mouse Scroll: Zoom");
	if (env->adj.projection == 1)
		mlx_string_put(mlx, win, 30, 110, WHITE,
			"Space: Toggle Projection (Currently Isometric)");
	else
		mlx_string_put(mlx, win, 30, 110, WHITE,
			"Space: Toggle Projection (Currently Parallel)");
}

int	mouse(int key, int x, int y, mlx_vars *env)
{
	(void)x;
	(void)y;
	if (key == 5)
		env->adj.zoom_factor = 1.03;
	else if (key == 4)
		env->adj.zoom_factor = 0.98;
	create_grid(env, env->map);
	return (0);
}

void	rotate(int key, mlx_vars *env)
{
	if (key == 13)
		env->adj.rotate_x = .25;
	if (key == 0)
		env->adj.rotate_z = -.05;
	if (key == 1)
		env->adj.rotate_x = -.25;
	if (key == 2)
		env->adj.rotate_z = .05;
}

void	translation(int key, mlx_vars *env)
{
	if (key == 123)
		env->adj.x_offset = -10;
	else if (key == 124)
		env->adj.x_offset = 10;
	else if (key == 126)
		env->adj.y_offset = -10;
	else if (key == 125)
		env->adj.y_offset = 10;
}
