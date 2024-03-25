/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:10:43 by chon              #+#    #+#             */
/*   Updated: 2024/03/25 16:22:27 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	free_and_return(char **str, int num)
{
	free_array(str);
	return (num);
}

double	factor_calc(double x, double y)
{
	if (x == 0 && y == 0)
		return (1);
	else
		return (min(2, 1440 / x, 900 / y));
}
