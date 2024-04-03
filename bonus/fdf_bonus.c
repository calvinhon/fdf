/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:41:49 by chon              #+#    #+#             */
/*   Updated: 2024/04/03 20:05:18 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	init_rotation(t_mlx_vars *env)
{
	if (env->adj.project)
	{
		rotate_map(z_r(init_matrix(3, 3), M_PI / 4), env);
		rotate_map(x_r(init_matrix(3, 3), atan(sqrt(2))), env);
		// stretch_transl(env->map, 1, 200, 100);
 		// printf("iso\n");
	}
	else if (!env->adj.project)
	{
		rotate_map(x_r_inverse(init_matrix(3, 3), atan(sqrt(2))), env);		
		rotate_map(z_r_inverse(init_matrix(3, 3), M_PI / 4), env);
		// stretch_transl(env->map, 1, -100, 100);
		// printf("parallel\n");
	}
	// adjust_grid(env->map);
}

void	setup_img(t_mlx_vars *env, char **array)
{
	int	i;

	reset_transformation(env);
	i = -1;
	env->map = collect_data_points(array);
	if (!env->map)
	{
		free_array(array);
		exit(0);
	}
	env->adj.project = 1;
	init_rotation(env);
	// adjust_grid(env->map);
	// stretch_transl(env->map, 1, 200, 100);
	set_controls(env);
	create_grid(env, env->map);
	mlx_loop(env->mlx);
	while (env->map[++i])
		free(env->map[i]);
	free(env->map);
}

t_mlx_vars	*init_env(void)
{
	t_mlx_vars	*env;

	env = (t_mlx_vars *)malloc(sizeof(t_mlx_vars));
	if (!env)
		return (NULL);
	env->mlx = mlx_init();
	if (!env->mlx)
	{
		free(env);
		return (NULL);
	}
	env->win = mlx_new_window(env->mlx, 1920, 1080, "fdf");
	env->img = mlx_new_image(env->mlx, 1920, 1080);
	env->addr = mlx_get_data_addr(env->img, &env->bpp, &env->l_len, &env->end);
	if (!env->win || !env->img || !env->addr)
	{
		free(env);
		return (NULL);
	}
	return (env);
}

char	*pull_elements(char *str)
{
	int		fd;
	char	*elements;
	char	*line;

	elements = NULL;
	str = ft_strjoin(ft_strdup("./test_maps/"), str);
	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		elements = ft_strjoin(elements, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(str);
	return (elements);
}

int	main(int ac, char **av)
{
	char		*elements;
	char		**array;
	t_mlx_vars	*env;

	if (ac == 2)
	{
		elements = pull_elements(av[1]);
		array = ft_split(elements, '\n');
		free(elements);
		if (!array || check_map(array) == 0)
		{
			ft_putstr_fd("Invalid map\n", 1);
			free(array);
			return (1);
		}
		env = init_env();
		if (!env)
		{
			free_array(array);
			return (1);
		}
		setup_img(env, array);
	}
	return (0);
}
