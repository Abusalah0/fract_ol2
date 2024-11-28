/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 01:09:41 by abdsalah          #+#    #+#             */
/*   Updated: 2024/11/28 01:09:57 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

double smooth_color(int iterations, int max_iterations, double zx, double zy)
{
    if (iterations == max_iterations)
        return max_iterations; // Represents "inside" the set
    double log_zn = log(zx * zx + zy * zy) / 2.0;
    double nu = log(log_zn / log(2)) / log(2);
    return iterations + 1 - nu; // Gives a smooth transition
}

int get_color(double smooth_value, int max_iterations)
{
    double t = smooth_value / max_iterations; // Normalize smooth_value to [0, 1]
    int r = (int)(9 * (1 - t) * t * t * t * 255);
    int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
    int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    return (r << 16) | (g << 8) | b; // Combine RGB to a single int
}
