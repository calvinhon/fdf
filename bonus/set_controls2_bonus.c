/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:19:04 by chon              #+#    #+#             */
/*   Updated: 2024/03/29 17:28:57 by chon             ###   ########.fr       */
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
	mlx_string_put(mlx, win, 30, 110, WHITE, "Space: Toggle Projection");
}

int	mouse(int key, mlx_vars *env)
{
	printf("%d\n", key);
	printf("zoom2:%f\n", env->adj->zoom_factor);
	// if (key == 5)
	// {
	// 	printf("OK");
	// 	env->adj->zoom_factor += 0.5;
	// }
	// else if (key == 4)	
	// 	env->adj->zoom_factor -= 0.5;
	if (env->adj->zoom_factor < 0.05)
		env->adj->zoom_factor = 0.05;
	create_grid(env, env->map);
	return (0);
}

// void	rotate(int key, mlx_vars *env)
// {
	
// }

// void	zoom(int key, mlx_vars *env)
// {
// 	if (key == 27)
// 		env->adj->zoom_factor = 1.1;
// 	else if (key == 24)
// 		env->adj->zoom_factor = 0.9;
// }

void	translation(int key, mlx_vars *env)
{
	if (key == 123 || key == 124)
	{
		if (key == 123)		
			env->adj->x_offset = -10;
		else if (key == 124)
			env->adj->x_offset = 10;
		env->adj->y_offset = 0;
	}
	else if (key == 126 || key == 125)
	{
		if (key == 126)		
			env->adj->y_offset = -10;
		else if (key == 125)
			env->adj->y_offset = 10;
		env->adj->x_offset = 0;
	}
}
