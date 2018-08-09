/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:42:07 by banthony          #+#    #+#             */
/*   Updated: 2018/08/10 00:25:37 by banthony         ###   ########.fr       */
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
		w->player.pos.angle -= w->player.spd_angle * w->time.delta;	// reset l'angle
	if (w->keypress[KEY_LEFT])
		w->player.pos.angle += w->player.spd_angle * w->time.delta;	// reset l'angle
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

static int find_intersection(t_wolf *w, t_vector a, t_vector b, t_vector *hitPoint)
{
	double	delta;
	int i;
	t_vector step;
	t_vector pt_d;

	delta = fabs(b.y - a.y);
	if (fabs(b.x - a.x) >= delta)
		delta = fabs(b.x - a.x);
	step.x = ((double)b.x - (double)a.x) / (double)delta;
	step.y = ((double)b.y - (double)a.y) / (double)delta;
	pt_d = (t_vector){a.x + 0.5, a.y + 0.5, 0};
	i = -1;
	while (++i < delta)
	{
		if ((pt_d.x / BLOC_SIZE) < w->map_size.x && (pt_d.y / BLOC_SIZE) < w->map_size.y)
		{
			if (w->map[(int)(pt_d.y) / BLOC_SIZE][(int)pt_d.x / BLOC_SIZE] > '0')
			{
				*hitPoint = pt_d;
				return (1);	// intersection trouve
			}
		}
		// Affichage FOV
//		put_pixel_img((t_coord){(int)pt_d.x, (int)pt_d.y, CLR}, BLUE, &w->img[GAME]);
		pt_d.x += step.x;
		pt_d.y += step.y;
	}
	return (0);
}

/*
**	NOTE:
**	Pour trouver l'orientation du mur, se baser sur la direction du rayon ?
**	Chute de fps enorme quand tout proche d'un mur
**	Monde inverse par rapport a la mini map
**	Revoir les calculs pour les optimiser pour les perfs
*/

static void raycast(t_wolf *w)
{
	t_vector end;
	t_vector hitPoint;
	double distHit;
	double hWall;
	int i;

	i = -1;
	hWall = 0;
	// FOV tracing
	while (++i < WIN_W)
	{
		end.x = (w->player.pos.x - (w->player.screenDist *
				d_cos((w->player.pos.angle + w->player.fov_half) - w->player.ray_dir[i])));
		end.y = (w->player.pos.y - (w->player.screenDist *
				d_sin((w->player.pos.angle + w->player.fov_half) - w->player.ray_dir[i])));
		if ((find_intersection(w, w->player.pos, end, &hitPoint)))
		{
			// Calcul de la distance projete sur l'axe vertical (delta y)
			// dist = cos(angle:Vertical/Hypotenuse) x longueurHypotenuse
			// longueurHypotenuse calc avec pythagore
			distHit = d_cos(w->player.fov_half - w->player.ray_dir[i])
				* sqrt((fabs(hitPoint.y - w->player.pos.y) * fabs(hitPoint.y - w->player.pos.y))
					  + (fabs(hitPoint.x - w->player.pos.x) * fabs(hitPoint.x - w->player.pos.x)));
			hWall = BLOC_SIZE / distHit * w->player.screenDist;
			// WALL
			trace(&w->img[GAME],
			  (t_coord){i, (int)(w->player.heightView - (hWall / 2)), CLR},
			  (t_coord){i, (int)(w->player.heightView + (hWall / 2)), CLR}, RED);
			// FLOOR
			trace(&w->img[GAME],
			  (t_coord){i, (int)(w->player.heightView + (hWall / 2)), CLR},
				  (t_coord){i, WIN_H, CLR}, 0x1f1f1f);
			// SKY
			trace(&w->img[GAME],
			  (t_coord){i, (int)(w->player.heightView - (hWall / 2)), CLR},
			  (t_coord){i, 0, CLR}, BLUE);
		}
	}
}

void		draw_game(void *wolf)
{
	t_wolf	*w;

	if (!(w = (t_wolf*)wolf))
		return ;
	fill_img(&w->img[MAP_I], MAP_OVERLAY);
	draw_map(w, w->map, w->map_size);
	put_pixel_img((t_coord){(int)(w->player.pos.x / BLOC_SIZE) * 48, (int)(w->player.pos.y / BLOC_SIZE) * 48, CLR}, GREEN, &w->img[MAP_I]);
	raycast(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME].ptr, 0, 0);
}
