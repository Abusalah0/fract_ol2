/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 00:42:40 by abdsalah          #+#    #+#             */
/*   Updated: 2024/11/29 01:14:21 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	init_fractal(t_fractal *fractal)
{
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->max_iter = MAX_ITER;
	fractal->julia_re = -0.512511498387847167;
	fractal->julia_im = 0.521295573094847167;
}

static void	init_graphics_struct(t_graphics *graphics)
{
	graphics->mlx = NULL;
	graphics->win = NULL;
	graphics->img = NULL;
	graphics->data = NULL;
	graphics->bpp = 0;
	graphics->line_len = 0;
	graphics->endian = 0;
	graphics->fractal = NULL;
}

void	init_graphics(t_graphics *graphics, t_fractal *fractal)
{
	init_graphics_struct(graphics);
	graphics->mlx = mlx_init();
	if (!graphics->mlx)
		error_exit("Failed to initialize MLX");
	graphics->win = mlx_new_window(graphics->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!graphics->win)
	{
		free_graphics(graphics);
		error_exit("Failed to create MLX window");
	}
	graphics->img = mlx_new_image(graphics->mlx, WIDTH, HEIGHT);
	if (!graphics->img)
	{
		free_graphics(graphics);
		error_exit("Failed to create MLX image");
	}
	graphics->data = (int *)mlx_get_data_addr(graphics->img, &graphics->bpp,
			&graphics->line_len, &graphics->endian);
	if (!graphics->data)
	{
		free_graphics(graphics);
		error_exit("Failed to get image data address");
	}
	graphics->fractal = fractal;
}
