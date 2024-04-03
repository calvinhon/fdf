/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:05:52 by chon              #+#    #+#             */
/*   Updated: 2024/04/03 16:52:56 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void free_db_array(double **array, int x)
{
	int i;

	i = -1;
	while (++i < x)
		free(array[i]);
	free(array);
}

void free_array(char **array)
{
	int i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void increment(t_pt_dets p1, t_pt_dets p2, int *x, int *y)
{
	if (p1.x > p2.x)
		*x = -1;
	if (p1.y > p2.y)
		*y = -1;
}

double **z_r(double **matrix, double x)
{
	matrix[0][0] = cos(x);
	matrix[0][1] = -sin(x);
	matrix[1][0] = sin(x);
	matrix[1][1] = cos(x);
	matrix[2][2] = 1;
	return (matrix);
}

double **x_r(double **matrix, double x)
{
	matrix[0][0] = 1;
	matrix[1][1] = cos(x);
	matrix[1][2] = -sin(x);
	matrix[2][1] = sin(x);
	matrix[2][2] = cos(x);
	return (matrix);
}
