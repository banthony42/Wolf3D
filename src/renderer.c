/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:01:58 by grdalmas          #+#    #+#             */
/*   Updated: 2018/08/28 16:28:43 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

// RENDERER

static void			trace_sky(t_img *img, t_coord start, t_hit_info hit)
{
	(void)img;
	(void)hit;
	while (start.y > 0)
	{
		put_pixel_img(start, BLUE_SKY, img);
		start.y--;
	}
}
/*
static void	trace_color(t_img *img, t_coord a, t_coord b, unsigned int color)
{
	intdelta;
	int i;
	t_vector step;
	t_vector pt_d;
	t_coord pt;
	if (abs(b.x - a.x) >= abs(b.y - a.y))
		delta = abs(b.x - a.x);
	else
		delta = abs(b.y - a.y);
	if (!delta)
		return ;
	step.x = (double)((b.x - a.x) / delta);
	step.y = (double)((b.y - a.y) / delta);
	pt_d.x = a.x;
	pt_d.y = a.y;
	i = -1;
	while (++i < delta)
	{
		pt.x = (int)pt_d.x;
		pt.y = (int)pt_d.y;
		put_pixel_img(pt, color, img);
		pt_d.x += step.x;
		pt_d.y += step.y;
	}
}*/

static void			trace_floor(t_img *img, t_coord start, t_hit_info hit, double hWall, t_wolf *w)
{
// Remplissage du sol avec couleur unie
/*	while (start.y < img->size.y)
	{
		put_pixel_img(start, DARK_GREY, img);
		start.y++;
	}
*/
	// Si le compilateur crie car une var est unused
	(void)start;
	(void)img;
	(void)hit;
	(void)hWall;
	(void)w;
	if (hit.dist < 0.01)
		return ;
	// Algo 1 qui marche pas encore bien	#ragekit
	t_coord floor_texel;
	t_vector floor;
	double dist;
	t_texture texture;
	double angle;
	(void)texture;
	(void)floor;
	(void)floor_texel;
	double incr = 180 / WIN_W;
	while (start.y < img->size.y)
	{
		angle = (start.x * incr) + w->cam.ray_dir[start.x];
		dist = (w->cam.heightView / ((start.y - (WIN_H / 2)))) * (w->cam.screenDist) / 16;
		floor.y = w->cam.pos.x + dist;
		floor.x = w->cam.pos.y + ((dist + ((1 - d_cos(angle)) * dist)) * d_sin(angle));
		floor_texel.x = (int)(fmod(floor.x, BLOC_SIZE));
		floor_texel.y = (int)(fmod(floor.y, BLOC_SIZE));
//		texture = (t_texture)w->map[(int)(floor.y / BLOC_SIZE)][(int)(floor.x / BLOC_SIZE)] - '0';
		put_pixel_from_txt(start, floor_texel, &w->texture[T_STONE], img);
		start.y++;
	}
}

static void			trace_textured_wall(t_img *img, t_coord start, int h_wall, t_hit_info hit)
{
	int		i;
	t_coord	pt;
	t_coord	ptt;

	(void)ptt;
	(void)img;
	i = -1;
	pt = start;
	ptt.x = (int)(hit.object.size.x * (fmod(hit.side, BLOC_SIZE) / BLOC_SIZE));
	while (++i < h_wall)
	{
		if (pt.y >= 0 && pt.y < WIN_H)
		{
			ptt.y = hit.object.size.y * i / h_wall;
			put_pixel_from_txt(pt, ptt, &hit.object, img);
		}
		pt.y = start.y + i;
	}
}

static void			trace_untextured_wall(t_img *img, t_coord start, t_cam cam, t_hit_info hit)
{
	int i;

	i = -1;
	while (++i < hit.h_wall)
	{
		if (((int)hit.point.y % BLOC_SIZE) == 0 && ((int)hit.point.x % BLOC_SIZE) == 0)
			put_pixel_img(start, 0xffffff, img);
		else if (((int)hit.point.y % BLOC_SIZE) == 0)	// FACE NORD OU SUD, (hit sur une ligne horizontale)
		{
			if (cam.pos.y < hit.point.y)			// FACE NORD, (Joueur au dessus du hit)
				put_pixel_img(start, RED, img);
			else
				put_pixel_img(start, BLUE, img);	// FACE SUD, (Joueur en dessous du hit)
		}
		else if (((int)hit.point.x % BLOC_SIZE) == 0)	// FACE EST OU OUEST, (hit sur ligne verticale)
		{
			if (cam.pos.x < hit.point.x)			// FACE OUEST, (Joueur a gauche du hit)
				put_pixel_img(start, GREEN, img);
			else
				put_pixel_img(start, YELLOW, img);	// FACE EST, (Joueur a droite du hit)
		}
		start.y++;
	}
}

void			renderer(t_wolf *w)
{
	t_coord	column_start;
	double	half_wall;
	int		i;

	i = -1;
	while (++i < WIN_W)
	{
		// WALL
		half_wall = w->hit[i].h_wall / 2;
		column_start.x = i;
		column_start.y = (int)(w->cam.heightView - half_wall);
		if (w->textured)
			trace_textured_wall(&w->img[GAME], column_start, (int)w->hit[i].h_wall, w->hit[i]);
		else
			trace_untextured_wall(&w->img[GAME], column_start, w->cam, w->hit[i]);
		// SKY
		trace_sky(&w->img[GAME], column_start, w->hit[i]);
		// FLOOR
		column_start.y = (int)(w->cam.heightView + half_wall);
		trace_floor(&w->img[GAME], column_start, w->hit[i], w->hit[i].h_wall, w);
	}
}
