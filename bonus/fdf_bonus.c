/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:41:49 by chon              #+#    #+#             */
/*   Updated: 2024/03/25 16:49:00 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	setup_img(mlx_vars *vars, char **array)
{
	t_data		img;
	pt_dets		**clean_map;
	int			i;

	i = -1;
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, "fdf");
	img.img = mlx_new_image(vars->mlx, 1920, 1080);
	clean_map = collect_data_points(array);
	if (!clean_map)
	{
		free_array(array);
		exit(0);
	}
	set_controls(vars);
	create_grid(vars, img, clean_map);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	fdf_legend(vars);
	while (clean_map[++i])
		free (clean_map[i]);
	free (clean_map);
}

char	*pull_elements(char *map)
{
	int		fd;
	char	*elements;
	char	*line;

	elements = NULL;
	map = ft_strjoin(ft_strdup("./test_maps/"), map);
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		elements = ft_strjoin(elements, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(map);
	return (elements);
}

int	main(int ac, char **av)
{
	char		**array;
	mlx_vars	*vars;

	if (ac == 2)
	{
		vars = malloc(sizeof(mlx_vars));
		if (!vars)
			return (1);
		array = ft_split(pull_elements(av[1]), '\n');
		if (!array || check_map(array) == 0)
		{
			ft_putstr_fd("Invalid map\n", 1);
			free(array);
			return (1);
		}
		vars->mlx = mlx_init();
		if (!vars->mlx)
		{
			free_array(array);
			free(vars);
			return (1);
		}
		setup_img(vars, array);
		mlx_loop(vars->mlx);
	}
	return (0);
}
