/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:41:45 by chon              #+#    #+#             */
/*   Updated: 2024/04/08 15:09:42 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	x_close(t_mlx_vars *env)
{
	int	i;

	i = -1;
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	free(env->mlx);
	while (env->map[++i])
		free(env->map[i]);
	free(env->map);
	free(env);
	exit(0);
	return (0);
}

int	key(int key, t_mlx_vars *env)
{
	if (key == 53)
		x_close(env);
	else if ((key >= 123 && key <= 126) | (key >= 83 && key <= 87)
		| (key >= 0 && key <= 2) | (key == 13) | (key == 27) | (key == 24))
		key_triggers(key, env);
	else if (key == 49)
		projection(env);
	else
		return (0);
	create_grid(env, env->map);
	return (0);
}

void	set_controls(t_mlx_vars *env)
{
	mlx_hook(env->win, 2, 0, key, env);
	mlx_hook(env->win, 4, 0, mouse, env);
	mlx_hook(env->win, 17, 0, x_close, env);
}
