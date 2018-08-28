/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:01:58 by grdalmas          #+#    #+#             */
/*   Updated: 2018/08/28 19:29:20 by banthony         ###   ########.fr       */
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

static void			trace_floor(t_img *img, t_coord start)
{
	while (start.y < img->size.y)
	{
		put_pixel_img(start, DARK_GREY, img);
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
		trace_floor(&w->img[GAME], column_start);
	}
}
