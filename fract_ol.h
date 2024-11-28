/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:04:41 by abdsalah          #+#    #+#             */
/*   Updated: 2024/11/29 02:35:22 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 840
# define HEIGHT 680
# define MAX_ITER 120
# define ESC_KEY 65307
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define UP_KEY 65362
# define DOWN_KEY 65364
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define ZOOM_FACTOR 1.2
# define MOVE_STEP 0.1

typedef struct s_complex
{
	double		real;
	double		imag;
}				t_complex;

typedef struct s_img
{
	void		*img_ptr;
	char		*pixels_ptr;
	int			bpp;
	int			endian;
	int			line_len;
}				t_img;

typedef struct s_fractal
{
	char		*name;
	void		*mlx_connection;
	void		*mlx_window;
	t_img		img;
	double		shift_x;
	double		shift_y;
	double		zoom;
	double		julia_re;
	double		julia_im;
	int			max_iter;
	int			type;
}				t_fractal;

typedef struct s_graphics
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*data;
	int			bpp;
	int			line_len;
	int			endian;
	t_fractal	*fractal;
}				t_graphics;

void			init_fractal(t_fractal *fractal);
void			init_graphics(t_graphics *graphics, t_fractal *fractal);
void			render_fractal(t_graphics *graphics);
int				key_handler(int keycode, t_graphics *graphics);
int				mouse_handler(int button, int x, int y, t_graphics *graphics);
void			error_exit(const char *message);
void			free_graphics(t_graphics *graphics);
int get_color(int iterations, int max_iterations);
double			smooth_color(int iterations, int max_iterations, double zx,
					double zy);
#endif