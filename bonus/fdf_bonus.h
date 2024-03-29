/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:28:27 by chon              #+#    #+#             */
/*   Updated: 2024/03/29 16:36:01 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define WHITE	0xFFFFFF
# define GOLD	0xFFD700
# define OLIVE	0x808000
# define LIME	0x32CD32
# define PURPLE	0x800080

typedef struct s_transform
{
	int		x_offset;
	int		y_offset;
	double	zoom_factor;
}	transform;

typedef struct s_ct_vars
{
	int	i;
	int	j;
	int	k;
	int	point_ct1;
}	ct_vars;

typedef struct s_line
{
	int	dy;
	int	dx;
	int xi;
	int yi;
	int	err;
	int	err2;
}	line;

typedef struct s_sizing
{
	double	min_x;
	double	min_y;
	double	max_x;
	double	max_y;
	double	min_z;
	double	max_z;
	double	t;
}	sizing;

typedef struct s_pt_dets
{
	double	x;
	double 	y;
	double 	z;
	int 	color;
	int		end;
}	pt_dets;

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
}	color;

typedef	struct s_mlx_vars
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			l_len;
	int			end;
	pt_dets		**map;
	transform	*adj;
}	mlx_vars;

int		check_map(char **array);
pt_dets	**collect_data_points(char **array);
void	create_grid(mlx_vars *env, pt_dets **map);
double 	**mult_matrix(int x, int y, double **matrix1, double **matrix2);
double 	**init_matrix(int x, int y);
void	rotate_map(double **r_matrix, pt_dets **map);
void	adjust_grid(pt_dets **map);
double 	min(int n, ...);
double 	max(int n, ...);
double 	**x_r(double **matrix, double x);
double 	**z_r(double **matrix, double x);
void 	stretch_transl(pt_dets **map, double factor, double t_x, double t_y);
void	set_controls(mlx_vars *env);
void	translation(int key, mlx_vars *env);
int		mouse(int key, mlx_vars *env);
void	zoom(int key, mlx_vars *env);
void	rotate(int key, mlx_vars *env);
void	fdf_legend(mlx_vars *env);
void	increment(pt_dets p1, pt_dets p2, int *x, int *y);
void	free_array(char **array);
void	free_db_array(double **array, int x);
double	factor_calc(double x, double y);
int		free_and_return(char **str, int num);
void	get_color(pt_dets **map);
int		calc_color(double fraction, double color1, double color2);

#endif
