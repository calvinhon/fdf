/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:17:42 by chon              #+#    #+#             */
/*   Updated: 2024/04/08 14:53:38 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_hex(char *str)
{
	int	i;

	i = 2;
	if (ft_strlen(str) > 10 || ft_strlen(str) < 3)
		return (0);
	if (!(str[0] == '0' && (str[1] == 'x' || str[1] == 'X')))
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
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (elmnts[i])
	{
		count++;
		i++;
		if (count > 2)
			return (0);
	}
	if (is_hex(elmnts[1]) == 0)
		return (0);
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
	t_ct_vars	a;
	char		**elmnts;
	char		**color;

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
	t_ct_vars	a;

	a.i = -1;
	a.j = 0;
	a.point_ct2 = 0;
	if (!array)
		return (0);
	while (array[++a.i])
	{
		a.point_ct2 = ct_non_spaces(array[a.i]);
		if (a.i == 0)
			a.point_ct1 = a.point_ct2;
		if (a.point_ct1 != a.point_ct2)
			return (0);
		a.j = 0;
	}
	return (check_elmnts(array));
}
