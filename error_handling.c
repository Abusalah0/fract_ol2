/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 00:43:43 by abdsalah          #+#    #+#             */
/*   Updated: 2024/11/29 00:44:53 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include <stdio.h>

void	error_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	free_graphics(t_graphics *graphics)
{
	if (graphics->img)
	{
		mlx_destroy_image(graphics->mlx, graphics->img);
		graphics->img = NULL;
	}
	if (graphics->win)
	{
		mlx_destroy_window(graphics->mlx, graphics->win);
		graphics->win = NULL;
	}
	if (graphics->mlx)
	{
		mlx_destroy_display(graphics->mlx);
		free(graphics->mlx);
		graphics->mlx = NULL;
	}
}
