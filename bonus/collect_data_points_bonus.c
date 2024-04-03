/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_data_points_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:06:11 by chon              #+#    #+#             */
/*   Updated: 2024/04/03 17:09:10 by chon             ###   ########.fr       */
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
		num++;
		while (str[i] && str[i] != ' ')
			i++;
	}
	if (str[i - 1] == ' ')
		num--;
	return (num);
}

t_pt_dets	**collect_data_points(char **array)
{
	t_ct_vars	a;
	char		**elmnts;
	t_pt_dets	**map;

	a.i = 0;
	a.j = 0;
	a.k = ct_non_spaces(array[0]);
	while (array[a.j])
		a.j++;
	map = malloc(sizeof(t_pt_dets) * (a.j + 1));
	if (!map)
		return (NULL);
	a.i = -1;
	while (++a.i < a.j)
	{
		elmnts = ft_split(array[a.i], ' ');
		map[a.i] = fill_map(elmnts, a.i, a.k);
		free_array(elmnts);
	}
	map[a.i] = NULL;
	get_color(map);
	return (map);
}
