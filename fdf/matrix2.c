/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:23:50 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/12 19:02:08 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			convert_3_to_2d(t_3d *d)
{
	t_index		i;
	
	i.y = 0;
	while (i.y < d->y)
	{
		i.x = 0;
		while (i.x < d->x)
		{
			d->mm[i.y][i.x] = apply_matrix_to_point(d->matrix, d->m[i.y][i.x]);
			d->n[i.y][i.x].y = d->offs.y + d->zoom *
				get_3d_y(d->mm[i.y][i.x].x,
						d->mm[i.y][i.x].y, d->mm[i.y][i.x].z, d);
			d->n[i.y][i.x].x = d->offs.x + d->zoom *
				get_3d_x(d->mm[i.y][i.x].x, d->mm[i.y][i.x].y);
			++i.x;
		}
		++i.y;
	}
	return (1);
}

t_vector	apply_matrix_to_point(float **m, t_vector v)
{
	t_vector	n;

	n.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
	n.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
	n.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];
	return (n);
}


float		**factor_matrix(float **a, float **b)
{
	float	**m;
	t_xyz	i;

	if (!(m = (float **)malloc(sizeof(float *) * 4)))
		return (0);
	i.y = -1;
	while (++i.y < 4 && (i.x = -1) != 0)
	{
		if (!(m[i.y] = (float *)malloc(sizeof(float) * 4)))
			return (0);
		while (++i.x < 4 && (i.z = -1) != 0)
		{
			while (++i.z < 4)
				m[i.y][i.x] += a[i.y][i.z] * b[i.z][i.x];
		}
	}
	return (m);
}

void	print_matrix(float **m)
{
	t_xyz	i;

	i.y = -1;
	while (++i.y < 4 && (i.x = -1) != 0)
	{
		while (++i.x < 4)
		{
			printf("%3f ", m[i.y][i.x]);
		}
		printf("\n");
	}
}

void		rotate(t_3d *d, char axis, char i)
{
	if (axis == 'z' || axis == 'a')
	{
		d->angle.z = (i == '+') ? d->angle.z + (5.625 * PI) / 18000000 :
						d->angle.z - (5.625 * PI) / 18000000;
		d->matrix = factor_matrix(d->matrix, matrix_rotation_z(d->angle.z));
	}
	if (axis == 'y' || axis == 'a')
	{
		d->angle.y = (i == '+') ? d->angle.y + (5.625 * PI) / 18000000 :
						d->angle.y - (5.625 * PI) / 18000000;
		d->matrix = factor_matrix(d->matrix, matrix_rotation_y(d->angle.y));
	}
	if (axis == 'x' || axis == 'a')
	{
		d->angle.x = (i == '+') ? d->angle.x + (5.625 * PI) / 18000000 :
						d->angle.x - (5.625 * PI) / 18000000;
		d->matrix = factor_matrix(d->matrix, matrix_rotation_x(d->angle.x));
	}
	print_matrix(d->matrix);
	convert_3_to_2d(d);
//	free(d->matrix);
//	d->matrix = NULL;
}
