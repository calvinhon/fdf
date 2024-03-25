/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:17:42 by chon              #+#    #+#             */
/*   Updated: 2024/03/13 19:42:23 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_hex(char *str)
{
	int	i;

	i = 2;
	if (ft_strlen(str) > 10 || ft_strlen(str) < 3)
		return (0);
	if (ft_strlen(str) > 2 && !(str[0] == '0'
			&& (str[1] == 'x' || str[1] == 'X')))
		return (0);
	if (ft_strlen(str) > 2)
	{
		while (str[i])
		{
			if (!(ft_isdigit(str[i]) || (str[i] >= 'a' && str[i] <= 'f')
					|| (str[i] >= 'A' && str[i] <= 'F')))
				return (0);
			i++;
		}
	}
	return (1);
}

int	is_decimal(char *str)
{
	int	i;

	i = 0;
	if (i == 0 && str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

int	check_color(char **elmnts)
{
	int		k;
	int		count;

	k = 0;
	count = 0;
	if (elmnts[1])
	{
		while (elmnts[1][k])
		{
			if (elmnts[1][k++] == ',')
				count++;
			if (count > 1)
				return (0);
		}
		if (is_hex(elmnts[1]) == 0)
			return (0);
	}
	return (1);
}

int	check_elmnts(char **array)
{
	int		i;
	int		j;
	char	**elmnts;

	i = 0;
	j = 0;
	while (array[i])
	{
		elmnts = ft_split(array[i], ' ');
		while (elmnts[j])
		{
			if (!ft_strchr(elmnts[j], ',') && !is_decimal(elmnts[j]))
				return (0);
			else if (check_color(ft_split(elmnts[j], ',')) == 0)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	check_map(char **array)
{
	int		i;
	int		cur_row_elmnts_ct;
	int		next_row_elmnts_ct;
	char	**row_elmnts;

	cur_row_elmnts_ct = 0;
	next_row_elmnts_ct = 0;
	i = 0;
	while (array[i + 1])
	{
		row_elmnts = ft_split(array[i], ' ');
		while (row_elmnts[cur_row_elmnts_ct])
			cur_row_elmnts_ct++;
		i++;
		row_elmnts = ft_split(array[i], ' ');
		while (row_elmnts[next_row_elmnts_ct])
			next_row_elmnts_ct++;
		if (cur_row_elmnts_ct != next_row_elmnts_ct)
			return (0);
		cur_row_elmnts_ct = 0;
		next_row_elmnts_ct = 0;
	}
	return (check_elmnts(array));
}
