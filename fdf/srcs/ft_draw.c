/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:21:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/22 14:44:08 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

/*
** creates a new image
*/

void	ft_create_image(t_3d *d)
{
	d->img.img ? mlx_destroy_image(d->img.mlx, d->img.img) : 0;
	d->img.img = mlx_new_image(d->img.mlx, WIDTH, HEIGHT);
	d->img.data_address = mlx_get_data_addr(d->img.img, &(d->img.bpp),
			&(d->img.line_size), &(d->img.endian));
}

/*
** Puts exactly one pixel in the image
** As d->c[y][x] is the color expressed as integer, we take the address
** of d->data_address and then cast it as (int *) before dereferencing to
** save color value inside.
** the d->l is used for night/day and transparency effects.
** a shade binary filter is applied by shifting right each color by 1 bit.
*/

void	put_pixel_in_img(t_3d *d, t_vector a, t_argb c)
{
	int			x;
	int			y;
	unsigned	color;
	unsigned	shade;

	x = round(a.x) + d->offs.x;
	y = round(a.y) + d->offs.y;

	shade = ((d->angle.x < 3 * PI / 2) && (d->angle.x > PI / 2)) ||
			((d->angle.y < 3 * PI / 2) && (d->angle.y > PI / 2)) ? 1 : 0;
	color = (ft_clamp((int)round(c.r + d->l.r), 0, 0xff) << (16 - shade)) +
		((ft_clamp((int)round(c.g + d->l.g), 0, 0xff) << (8 - shade))) +
		(ft_clamp(round(c.b + d->l.b), 0, 0xff) >> shade) +
		(ft_clamp((int)round(c.a + d->l.a), 0, 0xff) << 24);
	if (x >= 0 && y >= 0 && x <= WIDTH && y <= HEIGHT)
		*(int *)&d->img.data_address[(x * d->img.bpp / 8) +
			(y * d->img.line_size)] = color;
}

/*
** draw lines between points using Gressenham algorytm
** the condition evalues that the starting pixel is inside the frame
*/

void	lines_draw(t_3d *d, t_vector a, t_vector b, t_uixy c)
{
	t_fxy		dif;
	t_fxy		i;
	t_argb2		grad;
	int			pixel;
	double		tmp;

	dif.x = fabs(b.x - a.x);
	dif.y = fabs(b.y - a.y);
	tmp = (dif.x > dif.y) ? dif.x : dif.y;
	pixel = (!round(tmp)) ? 1 : round(tmp);
	i.x = dif.x / tmp * (a.x < b.x ? 1 : -1);
	i.y = dif.y / tmp * (a.y < b.y ? 1 : -1);
	grad = gradient(c.x, c.y, pixel);
	while (pixel--)
	{
		if ((a.x > WIDTH && a.x < 0) && (a.y > HEIGHT && a.y < 0))
			pixel = 0;
		put_pixel_in_img(d, a, grad.x);
		a.x += i.x;
		a.y += i.y;
		grad.x.r += grad.y.r;
		grad.x.g += grad.y.g;
		grad.x.b += grad.y.b;
		grad.x.a += grad.y.a;
	}
}

/*
** draw each lines starting from (y, x) to (y + 1, x) and (y, x + 1)
*/

void	draw(t_3d *d)
{
	t_index	i;
	t_uixy	color;

	i.y = 0;
	while (i.y < d->max.y - 1)
	{
		i.x = -1;
		while (++i.x < d->max.x - 1)
		{
			color.x = d->c[i.y][i.x];
			if (i.x < d->max.x - 1)
			{
				color.y = d->c[i.y][i.x + 1];
				lines_draw(d, d->mm[i.y][i.x], d->mm[i.y][i.x + 1], color);
			}
			if (i.y < d->max.y - 1)
			{
				color.y = d->c[i.y + 1][i.x];
				lines_draw(d, d->mm[i.y][i.x], d->mm[i.y + 1][i.x], color);
			}
		}
		++i.y;
	}
	lines_draw(d, d->mm[i.y - 1][i.x - 1], d->mm[i.y - 1][i.x - 1], color);
}

/*
** makes a 3d representation of the map and wait for user_input
*/

int		fdf(t_3d *d)
{
	int	i;

	i = 0;
	ft_create_image(d);
	apply_matrix(d);
	draw(d);
	mlx_put_image_to_window(d->img.mlx, d->img.w, d->img.img, 0, 0);
	if (d->help_display > 0)
		ft_settings(d);
	mlx_hook(d->img.w, KEYPRESS, KEYPRESSMASK, user_input, d);
	mlx_loop(d->img.mlx);
	return (0);
}
