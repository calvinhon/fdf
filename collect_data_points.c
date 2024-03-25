/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_data_points.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:06:11 by chon              #+#    #+#             */
/*   Updated: 2024/03/25 16:51:44 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	atoi_hex(char *str)
{
	int	num;
	int	i;
	int	x;

	num = 0;
	i = 2;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			x = str[i] - '0';
		else
		{
			if (str[i] >= 'a' && str[i] <= 'f')
				x = str[i] - 'a' + 10;
			else
				x = str[i] - 'A' + 10;
		}
		num = num * 16 + x;
		i++;
	}
	return (num);
}

void	point_color(char *str, pt_dets *point)
{
	char			**hex;

	hex = ft_split(str, ',');
	point->z = (double)ft_atoi(hex[0]);
	point->color = atoi_hex(hex[1]);
	free_array(hex);
}

pt_dets	*fill_data_points(char	**str, int row, int columns)
{
	pt_dets	*point;
	int		i;

	point = malloc(sizeof(pt_dets) * (columns + 1));
	if (!point)
		return (NULL);
	i = -1;
	while (++i < columns)
	{
		point[i].x = (double)i;
		point[i].y = (double)row;
		point[i].end = 1;
		point[i].z = 0;
		if (str[i] && !ft_strchr(str[i], ','))
		{
			point[i].z = (double)ft_atoi(str[i]);
			point[i].color = 0xffffff;
		}
		else if (str[i])
			point_color(str[i], &point[i]);
	}
	point[i].end = 0;
	return (point);
}

int	ct_non_spaces(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		num++;
		while (str[i] && str[i] != ' ')
			i++;
	}
	if (str[i - 1] == ' ')
		num--;
	return (num);
}

pt_dets	**collect_data_points(char **array)
{
	ct_vars	a;
	char	**elmnts;
	pt_dets	**data_points;

	a.i = 0;
	a.j = 0;
	a.k = ct_non_spaces(array[0]);
	while (array[a.j])
		a.j++;
	data_points = malloc(sizeof(pt_dets) * (a.j + 1));
	if (!data_points)
		return (NULL);
	a.i = -1;
	while (++a.i < a.j)
	{
		elmnts = ft_split(array[a.i], ' ');
		data_points[a.i] = fill_data_points(elmnts, a.i, a.k);
		free_array(elmnts);
	}
	data_points[a.i] = NULL;
	return (data_points);
}
