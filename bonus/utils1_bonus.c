/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:59:49 by chon              #+#    #+#             */
/*   Updated: 2024/03/21 18:48:21 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

double	max(int n, ...)
{
	va_list	args;
	double	max_num;
	double	cur;
	int i = 0;

	va_start(args, n);
	max_num = va_arg(args, double);
	printf("max_num starting is: %f\n", max_num);
	while (i < n - 1)
	{
		cur = va_arg(args, double);
		printf("cur is: %f\n", cur);
		if (cur > max_num)
			max_num = cur;
		i++;
	}
	va_end(args);
	printf("max_num: %f\n", max_num);
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
	// printf("factor:%.1f\n", factor);
	printf("trans2: %.0f, %.0f\n", t_x, t_y);
	while (map[idx.i])
	{
		while (map[idx.i][idx.j].end)
		{
			map[idx.i][idx.j].x = (map[idx.i][idx.j].x + t_x) * factor;
			map[idx.i][idx.j].y = (map[idx.i][idx.j].y + t_y) * factor;
			// printf("%.0f, %.0f\n", map[idx.i][idx.j].x, map[idx.i][idx.j].y);
			idx.j++;
		}
		idx.j = 0;
		idx.i++;
	}
}

double	**mult_matrix(int x, int y, double **matrix1, double **matrix2)
{
	double	**matrix_r;
	ct_vars	idx;
	double	num;

	matrix_r = init_matrix(x, y);
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
			matrix_r[idx.i][idx.j] = num;
			num = 0;
			idx.k = -1;
			idx.j++;
		}
		idx.j = 0;
		idx.i++;
	}
	return (matrix_r);
}

double	**init_matrix(int x, int y)
{
	double	**iso;
	int		i;

	iso = ft_calloc(x, sizeof(double));
	if (!iso)
		return (NULL);
	i = 0;
	while (i < x)
	{
		iso[i] = ft_calloc(y, sizeof(double));
		if (!iso[i])
			return (NULL);
		i++;
	}
	return (iso);
}
