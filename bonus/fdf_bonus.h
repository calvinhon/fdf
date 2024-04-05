/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:28:27 by chon              #+#    #+#             */
/*   Updated: 2024/04/05 18:25:09 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define WHITE 0xFFFFFF
# define GOLD 0xFFD700
# define OLIVE 0x808000
# define LIME 0x32CD32
# define PURPLE 0x800080
# define OFFSET 300

typedef struct s_transform
{
	int		init_x_offset;
	int		init_y_offset;
	double	init_zoom_factor;
	int		x_offset;
	int		y_offset;
	double	zoom_factor;
	double	rotate_z;
	double	rotate_x;
	int		project;
	double	height_factor;
}	t_transform;

typedef struct s_ct_vars
{
	int	i;
	int	j;
	int	k;
	int	point_ct1;
	int	point_ct2;
}	t_ct_vars;

typedef struct s_line
{
	int	dy;
	int	dx;
	int	xi;
	int	yi;
	int	err;
	int	err2;
}	t_line;

typedef struct s_sizing
{
	double	max_x;
	double	max_y;
	double	min_z;
	double	max_z;
	double	t;
}	t_sizing;

typedef struct s_t_pt_dets
{
	double	x;
	double	y;
	double	z;
	int		color;
	int		end;
}	t_pt_dets;

typedef struct s_mult_pts
{
	t_pt_dets	x1;
	t_pt_dets	x2;
	t_pt_dets	x3;
}	t_mult_pts;

typedef struct s_color
{
	int	r1;
	int	g1;
	int	b1;
	int	r2;
	int	g2;
	int	b2;
	int	r3;
	int	g3;
	int	b3;
	int	color;
}	t_color;

typedef struct s_t_mlx_vars
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			l_len;
	int			end;
	t_pt_dets	**map;
	t_transform	adj;
}	t_mlx_vars;

int			check_map(char **array);
t_pt_dets	**collect_data_points(char **array);
void		create_grid(t_mlx_vars *env, t_pt_dets **map);
int			ct_non_spaces(char *str);
double		min(int n, ...);
double		max(int n, ...);
double		init_zoom_calc(double x, double y);
void		init_rotation(t_mlx_vars *env);
t_pt_dets	rotate_z(t_pt_dets pt, t_mlx_vars *env);
t_pt_dets	rotate_x(t_pt_dets pt, t_mlx_vars *env);
void		set_controls(t_mlx_vars *env);
void		key_triggers(int key, t_mlx_vars *env);
int			mouse(int key, int x, int y, t_mlx_vars *env);
void		projection(t_mlx_vars *env);
void		fdf_legend(t_mlx_vars *env);
void		increment(t_pt_dets p1, t_pt_dets p2, int *x, int *y);
void		get_color(t_pt_dets **map);
int			calc_color(double fraction, double color1, double color2);
double		col_fract(t_pt_dets p1, t_pt_dets p2, double dx, double dy);
void		free_array(char **array);
int			free_and_return(char **str, int num);
int			err_msg_and_return(char *str, int num);

#endif
