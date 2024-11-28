/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:44:54 by abdsalah          #+#    #+#             */
/*   Updated: 2024/11/28 00:30:03 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "minilibx-linux/mlx.h"
#include <stdio.h>

void	init_fractal(t_fractal *fractal)
{
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->max_iter = MAX_ITER;
	fractal->julia_re = -0.512511498387847167;
	fractal->julia_im = 0.521295573094847167;
}

void init_graphics_struct(t_graphics *graphics)
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

void	free_graphics(t_graphics *graphics)
{
	if (graphics->img) {
		mlx_destroy_image(graphics->mlx, graphics->img);
		graphics->img = NULL;
	}
	if (graphics->win) {
		mlx_clear_window(graphics->mlx, graphics->win);
		mlx_destroy_window(graphics->mlx, graphics->win);
		graphics->win = NULL;
	}
	if (graphics->mlx) {
		mlx_destroy_display(graphics->mlx);
		free(graphics->mlx);
		graphics->mlx = NULL;
	}
}

void	init_graphics(t_graphics *graphics, t_fractal *fractal)
{
	init_graphics_struct(graphics);
	graphics->mlx = mlx_init();
	if (!graphics->mlx) {
		perror("Failed to initialize MLX");
		exit(EXIT_FAILURE);
	}
	graphics->win = mlx_new_window(graphics->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!graphics->win) {
		free_graphics(graphics);
		perror("Failed to create MLX window");
		exit(EXIT_FAILURE);
	}
	graphics->img = mlx_new_image(graphics->mlx, WIDTH, HEIGHT);
	if (!graphics->img) {
		free_graphics(graphics);
		perror("Failed to create MLX image");
		exit(EXIT_FAILURE);
	}
	graphics->data = (int *)mlx_get_data_addr(graphics->img, &graphics->bpp,
			&graphics->line_len, &graphics->endian);
	if (!graphics->data) {
		free_graphics(graphics);
		perror("Failed to get image data address");
		exit(EXIT_FAILURE);
	}
	graphics->fractal = fractal;
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;
	t_graphics	graphics;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fractol <fractal_name>", 2);
		ft_putendl_fd("Available fractals: mandelbrot, julia, burning_ship", 2);
		return (EXIT_FAILURE);
	}
	fractal.name = argv[1];
	if (strcmp(fractal.name, "mandelbrot") && strcmp(fractal.name, "julia")
		&& strcmp(fractal.name, "burning_ship"))
	{
		ft_putendl_fd("Invalid fractal name.", 2);
		return (EXIT_FAILURE);
	}
	init_fractal(&fractal);
	init_graphics(&graphics, &fractal);
	render_fractal(&graphics);
	mlx_key_hook(graphics.win, key_handler, &graphics);
	mlx_mouse_hook(graphics.win, mouse_handler, &graphics);
	mlx_loop(graphics.mlx);
	return (0);
}
