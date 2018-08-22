/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:01:58 by grdalmas          #+#    #+#             */
/*   Updated: 2018/08/22 17:56:11 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Algo de raycast basique
**	Un rayon pour chaque colonne de pixel de l'ecran.
**	L'angle de rayon est incremente avec: Angle de vue / Largeur ecran.
**	(FOV / WIN_W)
*/

// RENDERER

static void			trace_sky(t_img *img, t_coord start, t_hit_info hit)
{
	(void)hit;
	while (start.y > 0)
	{
		put_pixel_img(start, BLUE, img);
		start.y--;
	}
}

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
	(void)hit;
	(void)hWall;
	(void)w;

	// Algo 1 qui marche pas encore bien	#ragekit
	t_coord floor_texel;
	t_vector floor;
	floor.y = (double)w->cam.pos.y;
	floor.x = (double)w->cam.pos.x;
	double dist;
	t_texture texture;
		(void)texture;
	while (start.y < img->size.y)
	{
		dist = round((w->cam.heightView / ((start.y - (WIN_H / 2)))) * w->cam.screenDist);
		if (w->cam.pos.angle > 180)
		{
			floor.x = round((w->cam.pos.x + (dist * fabs(d_cos(w->cam.pos.angle + w->cam.ray_dir[start.x])))));
			floor.y = round((w->cam.pos.y + (dist * fabs(d_sin(w->cam.pos.angle + w->cam.ray_dir[start.x])))));
		}
		else
		{
			floor.x = round((w->cam.pos.x + (dist * fabs(d_sin(w->cam.pos.angle + w->cam.ray_dir[start.x])))));
			floor.y = round((w->cam.pos.y + (dist * fabs(d_cos(w->cam.pos.angle + w->cam.ray_dir[start.x])))));
		}
//		floor.y = w->cam.pos.y + dist;
		floor_texel.x = (int)(fmod(floor.x, BLOC_SIZE));
		floor_texel.y = (int)(fmod(floor.y, BLOC_SIZE));
//		floor_texel.x = (int)(fmod((start.x * fabs(d_sin(w->cam.pos.angle ))), BLOC_SIZE));
//		floor_texel.y = (int)(fmod((start.y * fabs(d_cos(w->cam.pos.angle ))), BLOC_SIZE));
///		floor_texel.x = (int)(fmod((start.x * fabs(d_tan(w->cam.pos.angle + w->cam.ray_dir[start.x]))), BLOC_SIZE));
//		floor_texel.y = (int)(fmod((start.y * fabs(d_cos(w->cam.pos.angle + w->cam.ray_dir[start.x]))), BLOC_SIZE));
//		printf("floor:%d x %d\n", floor_texel.x, floor_texel.y);
		texture = (t_texture)w->map[(int)(floor_texel.y / BLOC_SIZE)][(int)(floor_texel.x / BLOC_SIZE)] - '0';
		put_pixel_from_txt(start, floor_texel, &w->texture[T_STONE], img);
		start.y++;
	}
}

static void			trace_textured_wall(t_img *img, t_coord start, int h_wall, t_hit_info hit)
{
	int		i;
	t_coord	pt;
	t_coord	ptt;

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

void			renderer(t_wolf *w, int ray_x, t_hit_info hit, double h_wall)
{
	t_coord	column_start;
	double	half_wall = h_wall / 2;

	// WALL
	column_start.x = ray_x;
	column_start.y = (int)(w->cam.heightView - half_wall);
	trace_textured_wall(&w->img[GAME], column_start, (int)h_wall, hit);
	// SKY
	trace_sky(&w->img[GAME], column_start, hit);
	// FLOOR
	column_start.y = (int)(w->cam.heightView + half_wall);
	trace_floor(&w->img[GAME], column_start, hit, h_wall, w);
}
