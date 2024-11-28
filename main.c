/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:44:54 by abdsalah          #+#    #+#             */
/*   Updated: 2024/11/29 01:10:58 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;
	t_graphics	graphics;

	if (argc != 2 && argc != 4)
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
