/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:17:42 by chon              #+#    #+#             */
/*   Updated: 2024/03/25 16:41:28 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	is_hex(char *str)
{
	int	i;

	i = 2;
	if (ft_strlen(str) > 10 || ft_strlen(str) < 3)
		return (0);
	if (!(str[0] == '0'	&& (str[1] == 'x' || str[1] == 'X')))
		return (0);
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || (str[i] >= 'a' && str[i] <= 'f')
				|| (str[i] >= 'A' && str[i] <= 'F')))
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

int	check_elmnts(char **array)
{
	ct_vars	a;
	char	**elmnts;
	char	**color;

	a.i = -1;
	a.j = -1;
	while (array[++a.i])
	{
		elmnts = ft_split(array[a.i], ' ');
		while (elmnts[++a.j])
		{
			if (!ft_strchr(elmnts[a.j], ',') && !is_decimal(elmnts[a.j]))
				return (free_and_return(elmnts, 0));
			if (ft_strchr(elmnts[a.j], ','))
			{
				color = ft_split(elmnts[a.j], ',');
				if (check_color(color) == 0)
					return (free_and_return(color, 0));
				free_array(color);
			}
		}
		free_array(elmnts);
		a.j = -1;
	}
	return (1);
}

int	check_map(char **array)
{
	ct_vars	a;
	int		point_ct;

	a.i = 0;
	a.j = 0;
	point_ct = 0;
	while (array[a.i][point_ct] != ' ')
		point_ct++;
	while (array[++a.i])
	{
		while (array[a.i][a.j] != ' ')
			a.j++;
		if (a.j != point_ct)
			return (0);
		a.j = 0;
	}
	return (check_elmnts(array));
}
