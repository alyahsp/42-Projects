/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:07:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/18 01:54:45 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

/*
** mathematics functions used as define
*/

# define MAX(a, b)			(a > b ? a : b)
# define MIN(a, b)			(a < b ? a : b)

/*
** Board and Piece are saved on the stack
*/

# define BOARD			int b[f->max.y][f->max.x]
# define PIECE			int p[f->piece_dim.y][f->piece_dim.x]

/*
** relative position of player compared to cpu.
*/

# define POSITION		f->position
# define SE				3
# define SW				1
# define NE				9
# define NW				7
# define E				6
# define W				4
# define S				2
# define N				8

/*
** other usefull define
** SKIP_LINE to skip useless lines
** LAST it the last point sent to the Virtual Machine
** Exit messg is to exit;
*/

# define SKIP_LINE		get_next_line(0, &line)
# define PLY			f->player
# define LAST 			f->last_p

/*
** structure for (y, x) points
*/

typedef struct	s_index
{
	int			x;
	int			y;
}				t_index;
			
/*
** this list saved all valid positions
*/

typedef struct		s_point
{
	t_index			i;
	struct s_point	*next;
}					t_point;

/*
** board is the board stocked as char* while b is the board as int *
** max is max dimension y and x of the board
** player is the position of the player.
*/

typedef struct	s_filler
{
	int			cpu;
	int			player;
	int			turn;
	t_index		max;
	t_index		last_p;
	int			cpu_score;
	int			ply_score;
	int			position;
	t_index		dir;
	t_index		piece_dim;
	t_index		min_dim;
	t_index		max_dim;
	int			ver_hor;
	t_index		min_area;
	t_index		max_area;
	t_index		min_ply;
	t_index		max_ply;
	t_index		min_cpu;
	t_index		max_cpu;
	int			goal;
}				t_filler;

/*
** debug/display functions ~ debug.c//
*/

void			display_min(t_filler *f);//
void			display_board(t_index max, int b[max.y][max.x]);//
void			display_miniboard(t_filler *f, t_index min, t_index max, int b[f->max.y][f->max.x]);//debug
void			display_piece(t_index max, int p[max.y][max.x]);//
void			display_last(t_filler *f);//
void			display_turn_nb(t_filler *f);//
void			display_points(t_point **points);//
void			feed_board(t_index max, int b[max.y][max.x]);//debug

/*
** initialization and parsing functions ~ main.c
*/

void			filler_loop(t_filler *filler);
void			board_char2int(t_filler *f, char *s, int y, BOARD);
void			check_min_area(t_filler *f, BOARD);
void			check_max_area(t_filler *f, BOARD);

/*
** parsing and triming piece ~ parse.c
*/

void			get_piece_dimension(t_filler *f, char *line, BOARD);
int				check_min(t_filler *f, int y, int x, PIECE);
void			trim_piece(t_filler *f, PIECE);
void			filler_atoi(t_index *i, char *s);
void			return_piece(int a, int b);

/*
** solving algos ~ solver.c
*/

void			solver(t_filler *f, BOARD, PIECE);
void			surround(t_filler *f, BOARD, t_point *points);
int				g_d(t_filler *f, BOARD, t_index p);
int				next_to_cpu(t_filler *f, BOARD, t_index i);

/*
** PLAN B: break_through algo ~ break_through.c
*/

int				is_disadvantaged(t_filler *f, BOARD, t_index *ply_area);
int				has_captured_center(t_filler *f, BOARD);
void			get_to_center(t_filler *f, t_point *points);
int				get_relative_position(t_filler *f, t_index cpu_area, t_index i);
void			get_direction(t_filler *f, BOARD);
void			break_through(t_filler *f, BOARD, t_point *points);
int				score(t_filler *f, BOARD, t_index p);
int				g_d2(t_filler *f, BOARD, t_index p);

/*
** checks if sides are reached
*/

int				has_reached_top(t_filler *f, BOARD);
int				has_reached_bot(t_filler *f, BOARD);
int				has_reached_left(t_filler *f, BOARD);
int				has_reached_right(t_filler *f, BOARD);
int 			reach_borders(t_filler *f, BOARD);

/*
** Save relevant (y, x) valid positions inside a list ~ valid_positions.c
*/

int				put_piece(t_filler *f, BOARD, PIECE, t_point **points);
int				is_valid_position(t_filler *f, BOARD, PIECE, t_index c);
void			add_point(t_point **points, int y, int x);
t_point			*new_point(int y, int x);
void			free_saved_positions(t_point **points);

#endif
