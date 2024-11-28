#ifndef FRACT_OL_H
# define FRACT_OL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include <string.h>

#define WIDTH 840
#define HEIGHT 680
#define MAX_ITER 1200
#define ESC_KEY 65307
#define LEFT_KEY 65361
#define RIGHT_KEY 65363
#define UP_KEY 65362
#define DOWN_KEY 65364
#define MOUSE_SCROLL_UP 4
#define MOUSE_SCROLL_DOWN 5
#define ZOOM_FACTOR 1.2
#define MOVE_STEP 0.1

typedef struct	s_img
{
	void	*img_ptr; // pointer to image struct
	char	*pixels_ptr; // points to the actual pixels
	int		bpp;
	int		endian;
	int		line_len;
} 			t_img;

typedef struct	s_fractal
{
	char	*name;
	void	*mlx_connection; // mlx_init()
	void	*mlx_window;     // mlx_new_window()
	t_img	img; // Image structure

	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_re;
	double	julia_im;
	int		max_iter; // Value tied with image quality and rendering speed
	int		type; // Fractal type
} 			t_fractal;

typedef struct	s_graphics
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*data;
	int			bpp;
	int			line_len;
	int			endian;
	t_fractal	*fractal;
} 			t_graphics;
// Initialization functions
void init_fractal(t_fractal *fractal);
void init_graphics(t_graphics *graphics, t_fractal *fractal);

// Fractal calculation functions
int calculate_mandelbrot(double c_re, double c_im, int max_iterations);
int calculate_julia(double z_re, double z_im, double c_re, double c_im, int max_iterations);
int calculate_burning_ship(double c_re, double c_im, int max_iterations);

// Rendering and event handling
void render_fractal(t_graphics *graphics);
void zoom(t_graphics *graphics, double zoom_factor);
int key_handler(int keycode, t_graphics *graphics);
int mouse_handler(int button, int x, int y, t_graphics *graphics);

// Utility functions
void error_exit(const char *message);

//colors 
int get_color(double smooth_value, int max_iterations);
double smooth_color(int iterations, int max_iterations, double zx, double zy);
#endif