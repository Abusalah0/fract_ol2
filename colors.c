/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:34:59 by abdsalah          #+#    #+#             */
/*   Updated: 2024/11/29 02:36:50 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

t_color create_color(int r, int g, int b)
{
    t_color color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

t_color interpolate_color(t_color start, t_color end, double ratio)
{
    t_color result;
    if (ratio > 1.0)
        ratio = 1.0;
    if (ratio < 0.0)
        ratio = 0.0;
    result.r = start.r + (int)((end.r - start.r) * ratio);
    result.g = start.g + (int)((end.g - start.g) * ratio);
    result.b = start.b + (int)((end.b - start.b) * ratio);
    return result;
}

int get_color(int iterations, int max_iterations)
{
    t_color gradient[] = {
        create_color(66, 30, 15),   // Dark Brown
        create_color(25, 7, 26),    // Deep Purple
        create_color(9, 1, 47),     // Dark Blue
        create_color(4, 4, 73),     // Medium Blue
        create_color(0, 7, 100),    // Blue
        create_color(12, 44, 138),  // Lighter Blue
        create_color(24, 82, 177),  // Even Lighter Blue
        create_color(57, 125, 209), // Sky Blue
        create_color(134, 181, 229),// Light Sky Blue
        create_color(211, 236, 248),// Almost White
        create_color(241, 233, 191),// Light Yellow
        create_color(248, 201, 95), // Yellow
        create_color(255, 170, 0),  // Orange
        create_color(204, 128, 0),  // Dark Orange
        create_color(153, 87, 0),   // Brown
        create_color(106, 52, 3)    // Dark Brown
    };
    int num_colors = sizeof(gradient) / sizeof(gradient[0]);
    double ratio = (double)iterations / max_iterations;
    int start_idx = (int)(ratio * (num_colors - 1));
    int end_idx = start_idx + 1;
    if (end_idx >= num_colors)
        end_idx = start_idx; // Handle edge case
    double local_ratio = (ratio * (num_colors - 1)) - start_idx;
    t_color color = interpolate_color(gradient[start_idx], gradient[end_idx], local_ratio);
    return (color.r << 16) | (color.g << 8) | color.b; // Combine into RGB int
}
