/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_data_points_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:06:11 by chon              #+#    #+#             */
/*   Updated: 2024/04/05 20:19:05 by hbui-vu          ###   ########.fr       */
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

void	point_color(char *str, t_pt_dets *point)
{
	char	**hex;

	hex = ft_split(str, ',');
	point->z = (double)ft_atoi(hex[0]);
	point->color = atoi_hex(hex[1]);
	free_array(hex);
}

t_pt_dets	*fill_map(char **str, int row, int columns)
{
	t_pt_dets	*point;
	int			i;

	point = malloc(sizeof(t_pt_dets) * (columns + 1));
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
			point[i].color = 0;
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
		if (str[i])
			num++;
		while (str[i] && str[i] != ' ')
			i++;
	}
	return (num);
}

t_pt_dets	**collect_data_points(char **array)
{
	int			i;
	int			rows;
	int			cols;
	char		**elmnts;
	t_pt_dets	**map;

	i = 0;
	rows = 0;
	cols = ct_non_spaces(array[0]);
	while (array[rows])
		rows++;
	map = malloc(sizeof(t_pt_dets) * (rows + 1));
	if (!map)
		return (NULL);
	i = -1;
	while (++i < rows)
	{
		elmnts = ft_split(array[i], ' ');
		map[i] = fill_map(elmnts, i, cols);
		free_array(elmnts);
	}
	map[i] = NULL;
	get_color(map);
	return (map);
}
