/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:59:28 by abdsalah          #+#    #+#             */
/*   Updated: 2024/11/28 01:14:46 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

/*
000000011111111111111111122222233347E7AB322222111100000000000000000000000000000
000001111111111111111122222222333557BF75433222211111000000000000000000000000000
000111111111111111112222222233445C      643332222111110000000000000000000000000
011111111111111111222222233444556C      654433332211111100000000000000000000000
11111111111111112222233346 D978 BCF    DF9 6556F4221111110000000000000000000000
111111111111122223333334469                 D   6322111111000000000000000000000
1111111111222333333334457DB                    85332111111100000000000000000000
11111122234B744444455556A                      96532211111110000000000000000000
122222233347BAA7AB776679                         A32211111110000000000000000000
2222233334567        9A                         A532221111111000000000000000000
222333346679                                    9432221111111000000000000000000
234445568  F                                   B5432221111111000000000000000000
                                              864332221111111000000000000000000
234445568  F                                   B5432221111111000000000000000000
222333346679                                    9432221111111000000000000000000
2222233334567        9A                         A532221111111000000000000000000
122222233347BAA7AB776679                         A32211111110000000000000000000
11111122234B744444455556A                      96532211111110000000000000000000
1111111111222333333334457DB                    85332111111100000000000000000000
111111111111122223333334469                 D   6322111111000000000000000000000
11111111111111112222233346 D978 BCF    DF9 6556F4221111110000000000000000000000
011111111111111111222222233444556C      654433332211111100000000000000000000000
000111111111111111112222222233445C      643332222111110000000000000000000000000
000001111111111111111122222222333557BF75433222211111000000000000000000000000000
000000011111111111111111122222233347E7AB322222111100000000000000000000000000000
*/

int	calculate_mandelbrot(double c_re, double c_im, int max_iterations)
{
	double	z_re;
	double	z_im;
	int		iteration;
	double	temp;

	z_re = c_re;
	z_im = c_im;
	iteration = 0;
	while (z_re * z_re + z_im * z_im <= 4 && iteration < max_iterations)
	{
		temp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = temp;
		iteration++;
	}
	return (iteration);
}

int	calculate_julia(double z_re, double z_im, double c_re, double c_im,
		int max_iterations)
{
	int		iteration;
	double	temp;

	iteration = 0;
	while (z_re * z_re + z_im * z_im <= 4 && iteration < max_iterations)
	{
		temp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = temp;
		iteration++;
	}
	return (iteration);
}

int	calculate_burning_ship(double c_re, double c_im, int max_iterations)
{
	double	z_re;
	double	z_im;
	double	temp;
	int		iteration;

	z_re = c_re;
	z_im = c_im;
	iteration = 0;
	while (z_re * z_re + z_im * z_im <= 4 && iteration < max_iterations)
	{
		z_re = fabs(z_re);
		z_im = fabs(z_im);
		temp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = temp;
		iteration++;
	}
	return (iteration);
}

void	render_fractal(t_graphics *graphics)
{
	double	c_re;
	double	c_im;
	int		color;
	int		y;
	int		x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			c_re = (x - WIDTH / 2.0) * 4.0 / WIDTH / graphics->fractal->zoom
				+ graphics->fractal->shift_x;
			c_im = (y - HEIGHT / 2.0) * 4.0 / WIDTH / graphics->fractal->zoom
				+ graphics->fractal->shift_y;
			color = 0;
			if (graphics->fractal->name && strcmp(graphics->fractal->name,
					"mandelbrot") == 0)
				color = calculate_mandelbrot(c_re, c_im,
						graphics->fractal->max_iter) * 0x010101;
			else if (graphics->fractal->name && strcmp(graphics->fractal->name,
					"julia") == 0)
				color = calculate_julia(c_re, c_im, graphics->fractal->julia_re,
						graphics->fractal->julia_im,
						graphics->fractal->max_iter) * 0x010101;
			else if (graphics->fractal->name && strcmp(graphics->fractal->name,
					"burning_ship") == 0)
				color = calculate_burning_ship(c_re, c_im,
						graphics->fractal->max_iter) * 0x010101;
			graphics->data[y * WIDTH + x] = color;
		}
	}
	mlx_put_image_to_window(graphics->mlx, graphics->win, graphics->img, 0, 0);
}