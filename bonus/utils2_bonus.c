/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:05:52 by chon              #+#    #+#             */
/*   Updated: 2024/04/04 17:37:22 by chon             ###   ########.fr       */
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

void	increment(t_pt_dets p1, t_pt_dets p2, int *x, int *y)
{
	if (p1.x > p2.x)
		*x = -1;
	if (p1.y > p2.y)
		*y = -1;
}
