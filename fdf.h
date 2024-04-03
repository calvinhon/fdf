/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:28:27 by chon              #+#    #+#             */
/*   Updated: 2024/04/03 16:52:56 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include "libft/libft.h"
#include "mlx/mlx.h"

#define TEXT_COLOR 0xFFFFFF

typedef struct s_data
{
	void *img;
	char *addr;
	int bpp;
	int l_len;
	int endian;
} t_data;

typedef struct s_t_mlx_vars
{
	void *mlx;
	void *win;
} t_mlx_vars;

typedef struct s_ct_vars
{
	int i;
	int j;
	int k;
	int point_ct1;
} ct_vars;

typedef struct s_line
{
	int dy;
	int dx;
	int xi;
	int yi;
	int err;
	int err2;
} line;

typedef struct s_sizing
{
	double min_x;
	double min_y;
	double max_x;
	double max_y;
	double t;
	double factor;
} sizing;

typedef struct s_point
{
	double x;
	double y;
	double z;
	int color;
	int end;
} t_pt_dets;

int check_map(char **array);
t_pt_dets **collect_data_points(char **array);
void create_grid(t_data img, t_pt_dets **map);
double **mult_matrix(int x, int y, double **matrix1, double **matrix2);
double **init_matrix(int x, int y);
double min(int n, ...);
double max(int n, ...);
double **x_r(double **matrix, double x);
double **z_r(double **matrix, double x);
void stretch_transl(t_pt_dets **map, double factor, double t_x, double t_y);
void set_controls(t_mlx_vars vars);
void increment(t_pt_dets p1, t_pt_dets p2, int *x, int *y);
void free_array(char **array);
void free_db_array(double **array, int x);
double factor_calc(double x, double y);
int free_and_return(char **str, int num);

#endif
