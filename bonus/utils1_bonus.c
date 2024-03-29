/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:59:49 by chon              #+#    #+#             */
/*   Updated: 2024/03/29 15:05:56 by chon             ###   ########.fr       */
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

void	stretch_transl(pt_dets **map, double factor, double t_x, double t_y)
{
	ct_vars	idx;

	idx.i = 0;
	idx.j = 0;
	while (map[idx.i])
	{
		while (map[idx.i][idx.j].end)
		{
			map[idx.i][idx.j].x = map[idx.i][idx.j].x * factor + t_x;
			map[idx.i][idx.j].y = map[idx.i][idx.j].y * factor + t_y;
			idx.j++;
		}
		idx.j = 0;
		idx.i++;
	}
}

double	**mult_matrix(int x, int y, double **matrix1, double **matrix2)
{
	double	**new_matrix;
	ct_vars	idx;
	double	num;

	new_matrix = init_matrix(x, y);
	idx.i = 0;
	idx.j = 0;
	idx.k = -1;
	num = 0;
	while (idx.i < x)
	{
		while (idx.j < y)
		{
			while (++idx.k < x)
				num += matrix1[idx.i][idx.k] * matrix2[idx.k][idx.j];
			new_matrix[idx.i][idx.j] = num;
			num = 0;
			idx.k = -1;
			idx.j++;
		}
		idx.j = 0;
		idx.i++;
	}
	free(matrix2);
	return (new_matrix);
}

double	**init_matrix(int x, int y)
{
	double	**matrix;
	int		i;

	matrix = ft_calloc(x, sizeof(double));
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < x)
	{
		matrix[i] = ft_calloc(y, sizeof(double));
		if (!matrix[i])
			return (NULL);
		i++;
	}
	return (matrix);
}
