/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:42:07 by banthony          #+#    #+#             */
/*   Updated: 2018/08/10 14:07:52 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			eventk_game(int keyhook, void *wolf)
{
	t_wolf		*w;
	t_vector	pt;

	ft_bzero(&pt, sizeof(pt));
	if (!(w = (t_wolf*)wolf))
		return (0);
	if (keyhook == MLX_KEY_ESCAPE)
		w->current_page = MAIN_MENU;
	if (w->keypress[KEY_RIGHT])
		w->player.pos.angle += w->player.spd_angle * w->time.delta;	// reset l'angle
	if (w->keypress[KEY_LEFT])
		w->player.pos.angle -= w->player.spd_angle * w->time.delta;	// reset l'angle
	if (w->keypress[KEY_W])
		move_forward(w);
	if (w->keypress[KEY_S])
		move_back(w);
	if (w->keypress[KEY_D])
		move_right(w);
	if (w->keypress[KEY_A])
		move_left(w);
	return (0);
}

int			eventm_game(int button, int x, int y, void *wolf)
{
	(void)wolf;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

static t_texture find_intersection(t_wolf *w, t_vector a, t_vector b, t_vector *hitPoint)
{
	double	delta;
	int i;
	t_vector step;
	t_vector pt_d;
	t_coord map_point;

	delta = fabs(b.y - a.y);
	if (fabs(b.x - a.x) >= delta)
		delta = fabs(b.x - a.x);
	step.x = ((double)b.x - (double)a.x) / (double)delta;
	step.y = ((double)b.y - (double)a.y) / (double)delta;
	pt_d = (t_vector){a.x + 0.5, a.y + 0.5, 0};
	i = -1;
	while (++i < delta)
	{
		map_point.x = ((int)pt_d.x / BLOC_SIZE);
		map_point.y = ((int)pt_d.y / BLOC_SIZE);
		if (map_point.x < w->map_size.x && map_point.y < w->map_size.y)
		{
			if (w->map[map_point.y][map_point.x] > '0' && w->map[map_point.y][map_point.x] < '0' + T_DOOR)
			{
				*hitPoint = pt_d;
				return ((t_texture)(w->map[map_point.y][map_point.x] - '0'));	// intersection trouve
			}
		}
		pt_d.x += step.x;
		pt_d.y += step.y;
	}
	return (0);
}

static void	renderer(t_wolf *w, double hWallHalf, int ray_x, t_texture text_index)
{
	t_coord column_start;
	t_coord column_end;

	// WALL
	column_start.x = ray_x;
	column_start.y = (int)(w->player.heightView - hWallHalf);
	column_end.x = ray_x;
	column_end.y = (int)(w->player.heightView + hWallHalf);
	trace_texture(&w->img[GAME], column_start, column_end, &w->texture[text_index]);
	// SKY
	column_end.y = 0;
	trace_color(&w->img[GAME], column_start, column_end, BLUE);
	// FLOOR
	column_start.y = (int)(w->player.heightView + hWallHalf);
	column_end.y = WIN_H;
	trace_color(&w->img[GAME], column_start, column_end, 0x1f1f1f);
}

/*
**	NOTE:
**	Pour trouver l'orientation du mur, se baser sur la direction du rayon ?
**	Chute de fps enorme quand tout proche d'un mur
**	Revoir les calculs pour les optimiser pour les perfs
**	Detection des collision dans movements.c a revoir
**
**	Calcul de la distance projete sur l'axe vertical (delta y)
**	dist = cos(angle:Vertical/Hypotenuse) x longueurHypotenuse
**	longueurHypotenuse calc avec pythagore
*/

static void raycast(t_wolf *w)
{
	t_vector end;
	t_vector hitPoint;
	double distHit;
	double hWall;
	int i;
	t_texture objectHit;

	i = -1;
	hWall = 0;
	while (++i < WIN_W)
	{
		end.x = (w->player.pos.x - (w->player.lengthView *
				d_cos(w->player.pos.angle + w->player.fov_half + w->player.ray_dir[i])));
		end.y = (w->player.pos.y - (w->player.lengthView *
				d_sin(w->player.pos.angle + w->player.fov_half + w->player.ray_dir[i])));
		if ((objectHit = find_intersection(w, w->player.pos, end, &hitPoint)))
		{
			distHit = d_cos(w->player.fov_half + w->player.ray_dir[i])
				* sqrt(((hitPoint.y - w->player.pos.y) * (hitPoint.y - w->player.pos.y))
					  + ((hitPoint.x - w->player.pos.x) * (hitPoint.x - w->player.pos.x)));
			hWall = (BLOC_SIZE / distHit) * w->player.screenDist;
			renderer(w, hWall / 2, i, objectHit);
		}
	}
}

void		draw_game(void *wolf)
{
	t_wolf	*w;
	if (!(w = (t_wolf*)wolf))
		return ;
	raycast(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME].ptr, 0, 0);
}
