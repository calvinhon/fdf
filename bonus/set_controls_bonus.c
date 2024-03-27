/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:41:45 by chon              #+#    #+#             */
/*   Updated: 2024/03/27 14:25:14 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	fdf_legend(mlx_vars *vars)
{
	void	*mlx;
	void	*win;
	
	mlx = vars->mlx;
	win = vars->win;
	mlx_string_put(mlx, win, 30, 30, 0x32CD32, "CONTROLS LEGEND");
	mlx_string_put(mlx, win, 30, 50, TEXT_COLOR, "Arrow Keys: Translate");
}

int	x_close(mlx_vars *env)
{
	// (void)vars;
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	exit(0);
	return (0);
}

int	key(int key, mlx_vars *vars)
{
	if (key == 53)
		x_close(vars);
	printf("%i\n", key);
	if (key == 123)
		vars->adj->x_offset -= 50;
	else if (key == 124)
		vars->adj->x_offset += 50;
	else if (key == 126)
		vars->adj->y_offset -= 50;
	else if (key == 125)
		vars->adj->y_offset += 50;
	// printf("x_offset: %d\n", vars->adj->x_offset);
	return (0);
}

void	set_controls(mlx_vars *env)
{
	mlx_hook(env->win, 2, 0, key, env);
	mlx_hook(env->win, 17, 0, x_close, env);
}
