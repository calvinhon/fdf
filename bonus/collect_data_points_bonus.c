/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_data_points_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:06:11 by chon              #+#    #+#             */
/*   Updated: 2024/03/21 14:35:49 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	ct_vars	vars;
	char	**elmnts;
	pt_dets	**data_points;

	vars.i = 0;
	vars.j = 0;
	vars.k = ct_non_spaces(array[0]);
	while (array[vars.j])
		vars.j++;
	data_points = malloc(sizeof(pt_dets) * (vars.j + 1));
	if (!data_points)
		return (NULL);
	vars.i = -1;
	while (++vars.i < vars.j)
	{
		elmnts = ft_split(array[vars.i], ' ');
		data_points[vars.i] = fill_data_points(elmnts, vars.i, vars.k);
		free_array(elmnts);
	}
	data_points[vars.i] = NULL;
	return (data_points);
}
