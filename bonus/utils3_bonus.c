/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:10:43 by chon              #+#    #+#             */
/*   Updated: 2024/04/02 17:21:37 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	free_and_return(char **str, int num)
{
	free_array(str);
	return (num);
}

double	factor_calc(double x, double y)
{
	if (x == 0 && y == 0)
		return (1);
	else
		return (min(2, 1440 / x, 900 / y));
}

void	reset_transformation(mlx_vars *env)
{
	env->adj.x_offset = 0;
	env->adj.y_offset = 0;
	env->adj.zoom_factor = 1;
	env->adj.rotate_z = 0;
	env->adj.rotate_x = 0;
	env->adj.projection = 1;
	if (env->adj.projection == 1)
		env->adj.projection = 0;
}
