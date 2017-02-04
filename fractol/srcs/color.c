/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:19:44 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/04 18:48:49 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** d->color = 0 will produce rainbow hue
** d->color = 1 will make it irradiate
** 2 will color the inner shape with rainbow pixels
** 3 will make other color sets
** else it will be black and white
** 5 will be black and white (achromatic)
*/

static t_rgb	achromatic_color(t_rgb rgb)
{
	rgb.g = rgb.b;
	rgb.r = rgb.g;
	return (rgb);
}

unsigned		color_pixel(t_3d *d, int a)
{
	t_hsb	h;
	double	i;
	t_rgb	rgb;

	i = (double)a / d->f.max;
	h = (t_hsb) {.h = i * 360, .s = 1, .b = 1};
	if (d->color <= 2)
	{
		if (d->color == 0)
			h = (t_hsb) {.h = i * 360, .s = 1, .b = 1};
		else if (d->color == 1)
			h.h = i * ((float)rand()) / RAND_MAX * 4096;
		else if (d->color == 2)
			h.h = i * ((float)rand()) / RAND_MAX * 360;
		return (ft_hsb2hex(h));
	}
	rgb = ft_hex2rgb(ft_hsb2hex(h));
	if (d->color == 3)
		rgb.r = ft_fclamp((rgb.b + rgb.g) / 4, 0x30, 0xff);
	else if (d->color == 4)
		rgb.b = ft_fclamp((rgb.g + rgb.r) / 4, 0x30, 0xff);
	else
		rgb = achromatic_color(rgb);
	return (ft_rgb2hex(rgb));
}

/*
** trace a gradient line using starting color a and ending color b
*/

t_rgb2		ft_gradient(unsigned a, unsigned b, int pixel)
{
	t_rgb2	c;

	c.x.b = a & 0xFF;
	c.y.b = b & 0xFF;
	c.y.b = (c.y.b - c.x.b) / pixel;
	c.x.g = a >> 8 & 0xFF;
	c.y.g = b >> 8 & 0xFF;
	c.y.g = (c.y.g - c.x.g) / pixel;
	c.x.r = a >> 16 & 0xFF;
	c.y.r = b >> 16 & 0xFF;
	c.y.r = (c.y.r - c.x.r) / pixel;
	return (c);
}
