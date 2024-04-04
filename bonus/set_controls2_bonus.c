/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:19:04 by chon              #+#    #+#             */
/*   Updated: 2024/04/04 19:03:44 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	fdf_legend(t_mlx_vars *env)
{
	void	*mlx;
	void	*win;

	mlx = env->mlx;
	win = env->win;
	mlx_string_put(mlx, win, 30, 30, LIME, "CONTROLS LEGEND");
	mlx_string_put(mlx, win, 30, 50, WHITE, "Arrow Keys: Translate");
	mlx_string_put(mlx, win, 30, 70, WHITE, "-+: Height");
	mlx_string_put(mlx, win, 30, 90, WHITE, "WASD: Rotate");
	mlx_string_put(mlx, win, 30, 110, WHITE, "Mouse Scroll: Zoom");
	if (env->adj.project)
		mlx_string_put(mlx, win, 30, 130, WHITE,
			"Space: Toggle Projection (Currently Isometric)");
	else
		mlx_string_put(mlx, win, 30, 130, WHITE,
			"Space: Toggle Projection (Currently Parallel)");
}

void	projection(t_mlx_vars *env)
{
	env->adj.project = !env->adj.project;
	init_rotation(env);
	create_grid(env, env->map);
}

int	mouse(int key, int x, int y, t_mlx_vars *env)
{
	(void)x;
	(void)y;
	if (key == 5)
		env->adj.zoom_factor *= 1.03;
	else if (key == 4)
		env->adj.zoom_factor *= 0.98;
	create_grid(env, env->map);
	return (0);
}

void	key_triggers(int key, t_mlx_vars *env)
{
	if (key == 123)
		env->adj.x_offset -= 10;
	else if (key == 124)
		env->adj.x_offset += 10;
	else if (key == 126)
		env->adj.y_offset -= 10;
	else if (key == 125)
		env->adj.y_offset += 10;
	else if (key == 13)
		env->adj.rotate_x += .05;
	else if (key == 0)
		env->adj.rotate_z += .05;
	else if (key == 1)
		env->adj.rotate_x -= .05;
	else if (key == 2)
		env->adj.rotate_z -= .05;
	else if (key == 24)
		env->adj.height_factor *= 1.05;
	else if (key == 27)
		env->adj.height_factor *= .98;
}
