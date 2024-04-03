/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:28:27 by chon              #+#    #+#             */
/*   Updated: 2024/04/03 19:39:39 by chon             ###   ########.fr       */
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

typedef struct s_transform
{
	int		x_offset;
	int		y_offset;
	double	zoom_factor;
	double	rotate_z;
	double	rotate_x;
	int		project;
}	t_transform;

typedef struct s_ct_vars
{
	int	i;
	int	j;
	int	k;
	int	point_ct1;
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
	double	min_x;
	double	min_y;
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
double		**mult_matrix(int x, int y, double **matrix1, double **matrix2);
double		**init_matrix(int x, int y);
void		rotate_map(double **r_matrix, t_mlx_vars *env);
void		adjust_grid(t_pt_dets **map);
double		min(int n, ...);
double		max(int n, ...);
double		**x_r(double **matrix, double x);
double		**z_r(double **matrix, double x);
void		stretch_transl(t_pt_dets **map, double factor, double x, double y);
void		set_controls(t_mlx_vars *env);
void		translation(int key, t_mlx_vars *env);
int			mouse(int key, int x, int y, t_mlx_vars *env);
void		rotate(int key, t_mlx_vars *env);
void		fdf_legend(t_mlx_vars *env);
void		increment(t_pt_dets p1, t_pt_dets p2, int *x, int *y);
void		free_db_array(double **array, int x);
void		free_array(char **array);
double		factor_calc(double x, double y);
int			free_and_return(char **str, int num);
void		get_color(t_pt_dets **map);
int			calc_color(double fraction, double color1, double color2);
void		reset_transformation(t_mlx_vars *env);
void		projection(t_mlx_vars *env);
double		fraction(t_pt_dets p1, t_pt_dets p2, double dx, double dy);
void		init_rotation(t_mlx_vars *env);
double		**z_r_inverse(double **matrix, double x);
double		**x_r_inverse(double **matrix, double x);

#endif
