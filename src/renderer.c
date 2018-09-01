/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:01:58 by grdalmas          #+#    #+#             */
/*   Updated: 2018/09/01 02:15:07 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

// RENDERER

static unsigned int			fog_calcul(t_hit_info hit, unsigned int pixel, unsigned int fog_color, double fog_max)
{
	double fog_rate;
	unsigned int color;
	unsigned int r;
	unsigned int v;
	unsigned int b;

	fog_rate =  hit.real_dist / (fog_max - FOG_MIN);
	if (fog_rate < 0)
		fog_rate = 0;
	else if (fog_rate > 1)
		fog_rate = 1;

	r = (unsigned int)((1 - fog_rate) * ((pixel & RED) >> 16) + fog_rate * ((fog_color & RED) >> 16));
	v = (unsigned int)((1 - fog_rate) * ((pixel & GREEN) >> 8) + fog_rate * ((fog_color & GREEN) >> 8));
	b = (unsigned int)((1 - fog_rate) * (pixel & BLUE) + fog_rate * (fog_color & BLUE));
	color = (r << 16) | (v << 8) | b;
	return (color);
}

static void			trace_sky(t_img *img, t_coord start, t_hit_info hit, t_wolf *w)
{
	(void)hit;
	(void)w;
	while (start.y >= 0)
	{
		if (w->textured)
			put_pixel_img(start, BLUE_SKY, img);
//		else
//			put_pixel_img(start, fog_calcul(hit, BLUE_SKY, FOG_COLOR, w->max_dist), img);
		start.y--;
	}
}

static void			trace_floor(t_img *img, t_coord start, t_hit_info hit, t_wolf *w)
{
	(void)hit;
	(void)w;
	while (start.y < img->size.y)
	{
//			if (w->textured)
			put_pixel_img(start, DARK_GREY, img);
//		else
//			put_pixel_img(start, fog_calcul(hit, DARK_GREY, FOG_COLOR, w->max_dist), img);
		start.y++;
	}
}

static void			trace_textured_wall(t_wolf *w, t_coord start, int h_wall, t_hit_info hit)
{
	int			i;
	t_coord		pt;
	t_coord		ptt;
	t_texture	texture;
	t_door		*door;

	i = -1;
	pt = start;
	texture = hit.texture;
	ptt.x = (int)(hit.object.size.x * (fmod(hit.side, BLOC_SIZE) / BLOC_SIZE));
	if (hit.texture == T_DOOR)
	{
		if (((int)hit.point.x % BLOC_SIZE) == 0 || ((int)hit.point.x % BLOC_SIZE) == 63)
			texture = T_DOOR_SIDE;
		else if (((int)hit.point.y % BLOC_SIZE) == 0 || ((int)hit.point.y % BLOC_SIZE) == 63)
			texture = T_DOOR_SIDE;
		else if ((door = get_door(w, hit.point, 0, 0)))
			ptt.x -= door->timer * hit.object.size.x;
	}
	while (++i < h_wall)
	{
		if (pt.y >= 0 && pt.y < WIN_H)
		{
			ptt.y = hit.object.size.y * i / h_wall;
			if (!DRAWING_MODE)
				put_pixel_from_txt(pt, ptt, &w->texture[texture], &w->img[GAME]);
		}
		pt.y = start.y + i;
	}
}

static void			trace_untextured_wall(t_img *img, t_coord start, t_cam cam, t_hit_info hit, double fog_max)
{
	int i;

	i = -1;
	while (++i < hit.h_wall)
	{
		if (((int)hit.point.y % BLOC_SIZE) == 0 && ((int)hit.point.x % BLOC_SIZE) == 0)
			put_pixel_img(start, fog_calcul(hit, WHITE, FOG_COLOR, fog_max), img);
		else if (((int)hit.point.y % BLOC_SIZE) == 0)	// FACE NORD OU SUD, (hit sur une ligne horizontale)
		{
			if (cam.pos.y < hit.point.y)			// FACE NORD, (Joueur au dessus du hit)
				put_pixel_img(start, fog_calcul(hit, RED, FOG_COLOR, fog_max), img);
			else
				put_pixel_img(start, fog_calcul(hit, BLUE, FOG_COLOR, fog_max), img);	// FACE SUD, (Joueur en dessous du hit)
		}
		else if (((int)hit.point.x % BLOC_SIZE) == 0)	// FACE EST OU OUEST, (hit sur ligne verticale)
		{
			if (cam.pos.x < hit.point.x)			// FACE OUEST, (Joueur a gauche du hit)
				put_pixel_img(start, fog_calcul(hit, GREEN, FOG_COLOR, fog_max), img);
			else
				put_pixel_img(start, fog_calcul(hit, YELLOW, FOG_COLOR, fog_max), img);	// FACE EST, (Joueur a droite du hit)
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
			trace_textured_wall(w, column_start, (int)w->hit[i].h_wall, w->hit[i]);
		else
			trace_untextured_wall(&w->img[GAME], column_start, w->cam, w->hit[i], w->max_dist);
		// SKY
		trace_sky(&w->img[GAME], column_start, w->hit[i], w);
		// FLOOR
		column_start.y = (int)(w->cam.heightView + half_wall) - 2;
		trace_floor(&w->img[GAME], column_start, w->hit[i], w);
	}
}






