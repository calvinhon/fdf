/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:10:43 by chon              #+#    #+#             */
/*   Updated: 2024/04/03 18:29:08 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

double	**z_r_inverse(double **matrix, double x)
{
	matrix[0][0] = cos(x);
	matrix[0][1] = sin(x);
	matrix[1][0] = -sin(x);
	matrix[1][1] = cos(x);
	matrix[2][2] = 1;
	return (matrix);
}

double	**x_r_inverse(double **matrix, double x)
{
	matrix[0][0] = 1;
	matrix[1][1] = cos(x);
	matrix[1][2] = sin(x);
	matrix[2][1] = -sin(x);
	matrix[2][2] = cos(x);
	return (matrix);
}

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

void	reset_transformation(t_mlx_vars *env)
{
	env->adj.x_offset = 0;
	env->adj.y_offset = 0;
	env->adj.zoom_factor = 1;
	env->adj.rotate_z = 0;
	env->adj.rotate_x = 0;
}
