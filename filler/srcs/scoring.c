/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scoring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 01:57:21 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/20 03:13:11 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** check if there is a computer piece on the left side the following way:
**
** X
** . X
** X . O
** . .
** .
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
		i.y = (p.y - (f->goal & 1) * ray >= 0) ? p.y - (f->goal & 1) * ray : 0;
		max.y = (p.y + (f->goal & 8) * ray <= f->max.y) ?
			p.y + (f->goal & 1) * ray : f->max.y;
		while (i.y < max.y)
		{
			if (b[i.y][i.x] >> 1)
				score -= (p.x == i.x ? 100 : p.x - i.x + ray);
			else
				++score;
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
		i.y = (p.y - (f->goal & 1) * ray >= 0) ? p.y - (f->goal & 1) * ray : 0;
		max.y = (p.y + (f->goal & 8) * ray <= f->max.y) ?
			p.y + (f->goal & 1) * ray : f->max.y;
		while (i.y < max.y)
		{
			if (b[i.y][i.x] >> 1)
				score -= (p.x == i.x ? 100 : p.x - i.x + ray);
			else
				++score;
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
		i.x = (p.x - (f->goal & 2) * ray >= 0) ? p.x - (f->goal & 1) * ray : 0;
		max.x = (p.x + (f->goal & 4) * ray <= f->max.x) ?
			p.x + (f->goal & 1) * ray : f->max.x;
		while (i.x < max.x)
		{
			if (b[i.y][i.x] >> 1)
				score -= (p.y == i.y ? 100 : p.y - i.y + ray);
			else
				++score;
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
		i.x = (p.x - (f->goal & 2) * ray >= 0) ? p.x - (f->goal & 1) * ray : 0;
		max.x = (p.x + (f->goal & 4) * ray <= f->max.x) ?
			p.x + (f->goal & 1) * ray : f->max.x;
		while (i.x < max.x)
		{
			if (b[i.y][i.x] >> 1)
				score -= (p.y == i.y ? 100 : p.y - i.y + ray);
			else
				++score;
			++i.x;
		}
	}
	return (score);
}
