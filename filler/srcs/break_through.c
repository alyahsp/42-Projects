/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_through.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:56:39 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/20 01:05:52 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** strategy involved if the opponent has placement superiority
*/

int		is_disadvantaged(t_filler *f, BOARD, t_index *ply_area)
{
	t_index	i;
	t_index cpu_area;

	cpu_area = (t_index) {.x = 0, .y = 0};
	i.y = f->min_area.y - 1;
	while (++i.y <= f->max_area.y)
	{
		i.x = f->min_area.x - 1;
		while (++i.x <= f->max_area.x)
		{
			if (b[i.y][i.x] >> 1 && ++f->cpu_score)
			{
				cpu_area.y += i.y;
				cpu_area.x += i.x;
			}
			else if (b[i.y][i.x] && ++f->ply_score)
			{
				ply_area->y += i.y;
				ply_area->x += i.x;
			}
		}
	}
	return (get_relative_position(f, cpu_area, *ply_area));
}

/*
** function get player's position compared to computer
** SE = South East, NW = North West... etc;
*/

int		get_relative_position(t_filler *f, t_index cpu_area, t_index i)
{
	cpu_area.y /= f->cpu_score;
	cpu_area.x /= f->cpu_score;
	i.y = i.y / f->ply_score - cpu_area.y;
	i.x = i.x / f->ply_score - cpu_area.x;
	if (i.y > 0 && i.x)
		POSITION = (i.x > 0) ? SE : SW;
	else if (i.y < 0 && i.x)
		POSITION = (i.x > 0) ? NE : NW;
	else if (!i.x)
		POSITION = (i.y > 0) ? S : N;
	else
		POSITION = (i.x > 0) ? E : W;
	return ((f->min_area.y > f->max_area.y - f->max.y &&
		(POSITION == SW || POSITION == SE || POSITION == S))
		|| ((f->min_area.x > f->max_area.x - f->max.x) &&
		(POSITION == NE || POSITION == E || POSITION == SE))
		|| ((f->min_area.x <= f->max_area.x - f->max.x) &&
		(POSITION == NW || POSITION == W || POSITION == SW))
		|| ((f->min_area.y <= f->max_area.y - f->max.y) &&
		(POSITION == NW || POSITION == NE || POSITION == N)));
}

/*
** check if we are in the central area compared to cpu
** we light bit 1 if player and bit 2 if cpu.
** if both bits are lighted on a row or on a column we are close enough
*/

int		has_captured_center(t_filler *f, int b[f->max.y][f->max.x])
{
	t_index	i;
	int		check;

	i.y = f->min_area.y - 1;
	while (++i.y < f->max_area.y)
	{
		i.x = f->min_area.x - 1;
		check = 0;
		while (++i.x < f->max_area.x)
			check |= b[i.y][i.x];
		if ((check & 1) && (check & 2))
			return (1);
	}
	i.x = f->min_area.x - 1;
	while (++i.x < f->max_area.x)
	{
		i.y = f->min_area.y - 1;
		check = 0;
		while (++i.y < f->max_area.y)
			check |= b[i.y][i.x];
		if ((check & 1) && (check & 2))
			return (1);
	}
	return (0);
}

/*
** try to break through to be fight on equal ground
*/

void	break_through(t_filler *f,  int b[f->max.y][f->max.x], t_point *points)
{
	LAST = points->i;
	if ((f->goal & 2) || (f->goal & 4))//
		ft_putendl_fd((f->goal & 2) ? "to the left" : "to the right", 2);///
	if ((f->goal & 1) || (f->goal & 8))//
		ft_putendl_fd((f->goal & 1) ? "to the top" : "to the bot", 2);//
	while (points)
	{
		if (reach_borders(f, b, points->i) < reach_borders(f, b, LAST))
			LAST = points->i;
		points = points->next;
	}
}

/*
** check if the piece is rather horizontal (f->ver_hor < 0)
** or vertical (f->ver_hor > 0), if horizontal it will check the x distance
** from the relevant side
*/
/*
int		reach_borders(t_filler *f, t_index p)
{
	t_index	i;
	int		distance;
	int		tmp;

	distance = f->max.y * f->max.y + f->max.x * f->max.x;
	tmp = 0;
	if ((f->goal & 2) || (f->goal & 4))
	{
		i.x = ((f->goal & 2) ? 0 : f->max.x - 1);
		tmp = (i.x - p.x) * (i.x - p.x) / (f->max_dim.x + 1);
	}
	if ((f->goal & 1) || (f->goal & 8))
	{
		i.y = ((f->goal & 1) ? 0 : f->max.y - 1);
		distance = (i.y - p.y) * (i.y - p.y) / (f->max_dim.y + 1);
	}
	distance = tmp < distance ? tmp : distance;
	return (distance);
}
*/
/*
t_index		calculate(t_filler *f)
{
	t_index		i;

	i = (t_index) {.y = 0, .x = 0};
	if (f->ver_hor < 0 && ((f->goal & 2) || (f->goal & 4)))
	{
		i.x = ((f->goal & 2) ? 0 : f->max.x - 1);

	}
	else if ((f->goal & 1) || (f->goal & 8))
	{
		i.y = ((f->goal & 1) ? 0 : f->max.y - 1);
	}
	else if ((f->goal & 2) || (f->goal & 4))
	{
		i.x = ((f->goal & 2) ? 0 : f->max.x - 1);
	}
	return (i);
}

t_index	get_way_distance(t_filler *f, BOARD, t_index p)
{
	t_index		i;
	int			distance;
	int			tmp;

	distance = f->max.y * f->max.y + f->max.x * f->max.x;
	i.y = -1;
	i.x = -1;
	p = calculate(f); 
	while (++i.y < f->max.y)
	{
		i.x = -1;
		while (++i.x < f->max.x)
		{
			tmp = (i.y - p.y) * (i.y - p.y) + (i.x - p.x) * (i.x - p.x);
			if ((b[i.y][i.x] >> 1) && tmp < distance)
				if ((distance = tmp) == 2)
					return (i);
		}
	}
	return (i);
}

int		reach_borders(t_filler *f, int b[f->max.y][f->max.x], t_index p)
{
	t_index	i;
	int		score;

	score = 0;
	i = get_score(f, b, p);
	distance = ((i.y - p.y) * (i.y - p.y) + (i.x - p.x) * (i.x - p.x));
	return (score);
}
*/

int		score_left(t_filler *f, int b[f->max.y][f->max.x], t_index p)
{
	t_index		i;
	int			score;
	t_index		max;
	int			ray;

	score = 0;
	ray = 5;
	i.x = p.x + 1;
	while (--i.x >= 0 && ++ray < 3)
	{
		i.y = (p.y - ray >= 0) ? p.y - ray : 0;
		max.y = (p.y + ray <= f->max.y) ? p.y + ray : f->max.y;
		while (i.y < max.y)
		{
			if (b[i.y][i.x])
				score = score + ((b[i.y][i.x] >> 1) ? ray - p.y : (p.y - ray) >> 2);
			++i.y;
		}
		++ray;
	}
	return (score < 0 ? 0 : 1);
}

int		score_right(t_filler *f, int b[f->max.y][f->max.x], t_index p)
{
	t_index		i;
	int			score;
	t_index		max;
	int			ray;

	score = 0;
	ray = 0;
	i.x = p.x - 1;
	while (++i.x < f->max.x && ++ray < 3)
	{
		i.y = (p.y - ray >= 0) ? p.y - ray : 0;
		max.y = (p.y + ray <= f->max.y) ? p.y + ray : f->max.y;
		while (i.y < max.y)
		{
			if (b[i.y][i.x])
				score = score + ((b[i.y][i.x] >> 1) ? ray - p.y : (p.y - ray) >> 2);
			++i.y;
		}
		++ray;
	}
	return (score < 0 ? 0 : 1);
}

int		score_top(t_filler *f, int b[f->max.y][f->max.x], t_index p)
{
	t_index		i;
	int			score;
	t_index		max;
	int			ray;

	score = 0;
	ray = -1;
	i.y = p.y - 1;
	while (--i.y >= 0 && ++ray < 3)
	{
		i.x = (p.x - ray >= 0) ? p.x - ray : 0;
		max.x = (p.x + ray <= f->max.y) ? p.x + ray : f->max.x;
		while (i.x < max.x)
		{
			if (b[i.y][i.x])
				score = score + ((b[i.y][i.x] >> 1) ? ray - p.x : (p.x - ray) >> 2);
			++i.x;
		}
	}
	return (score);
}

int		score_bot(t_filler *f, int b[f->max.y][f->max.x], t_index p)
{
	t_index		i;
	int			score;
	t_index		max;
	int			ray;

	score = 0;
	ray = -1;
	i.y = p.y - 1;
	while (++i.y < f->max.y && ++ray < 3)
	{
		i.x = (p.x - ray >= 0) ? p.x - ray : 0;
		max.x = (p.x + ray <= f->max.y) ? p.x + ray : f->max.x;
		while (i.x < max.x)
		{
			if (b[i.y][i.x])
				score = score + ((b[i.y][i.x] >> 1) ? ray - p.x : (p.x - ray) >> 2);
			++i.x;
		}
	}
	return (score);
}

int		reach_borders(t_filler *f, int b[f->max.y][f->max.x], t_index p)
{
	t_index		i;
	int			distance;
	int			tmp;
	t_index		i2;
	int			tmp2;

	i2.y = ((f->goal & 1) ? score_top(f, b, p) : score_bot(f, b, p));
	i2.x = ((f->goal & 2) ? score_left(f, b, p) : score_right(f, b, p));
	i2.y /= f->max_dim.y;
	i2.x /= f->max_dim.x;
	tmp2 = (i2.x + i2.y);
	tmp2 *= tmp2 * tmp2 * tmp2;
	i.y = -1;
	while (++i.y < f->max.y)
	{
		i.x = -1;
		while (++i.x < f->max.x)
		{
			if (b[i.y][i.x] >> 1)
			{
				tmp = (i.y - p.y) * (i.y - p.y) + (i.x - p.x) * (i.x - p.x) - tmp2;
				if (tmp < distance)
					distance = tmp;
			//	if (tmp < distance)
			//		if ((distance = tmp) == 2)
			//			return (distance);
			}
		}
	}
	return (distance);
}