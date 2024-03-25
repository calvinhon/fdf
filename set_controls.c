/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:41:45 by chon              #+#    #+#             */
/*   Updated: 2024/03/25 15:38:13 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	x_close(mlx_vars *vars)
{
	(void)vars;
	exit(0);
	return (0);
}

int	key_close(int key, mlx_vars *vars)
{
	if (key == 53)
		x_close(vars);
	return (0);
}

void	set_controls(mlx_vars vars)
{
	mlx_hook(vars.win, 2, 0, key_close, &vars);
	mlx_hook(vars.win, 17, 0, x_close, &vars);
}
