/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:05:52 by chon              #+#    #+#             */
/*   Updated: 2024/04/05 18:06:57 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

int	free_and_return(char **str, int num)
{
	free_array(str);
	return (num);
}

int	err_msg_and_return(char *str, int num)
{
	ft_putstr_fd(str, 1);
	return (num);
}

double	init_zoom_calc(double x, double y)
{
	if (x == 0 && y == 0)
		return (1);
	else
		return (min(2, 720 / x, 480 / y));
}

void	increment(t_pt_dets p1, t_pt_dets p2, int *x, int *y)
{
	if (p1.x > p2.x)
		*x = -1;
	if (p1.y > p2.y)
		*y = -1;
}
