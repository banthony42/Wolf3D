/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:01:58 by grdalmas          #+#    #+#             */
/*   Updated: 2018/08/16 09:14:44 by banthony         ###   ########.fr       */
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
	(void)hit;
/*	while (start.y < img->size.y)
	{
		put_pixel_img(start, DARK_GREY, img);
		start.y++;
	}*/

	(void)hWall;

//	double floorDist;
//	double weight;
//	t_vector current_floor;
//	t_coord floorWall;
	t_coord floor_texel;
/*
	floorWall.x = start.x;
	floorWall.y = start.y;
	while (start.y < img->size.y)
	{
		floorDist = w->cam.heightView / (2.0 * start.y / w->cam.heightView);
		weight = floorDist / hit.dist;
		current_floor.x = weight * floorWall.x + (1.0 - weight) * w->cam.pos.x / BLOC_SIZE;
		current_floor.y = weight * floorWall.y + (1.0 - weight) * w->cam.pos.y / BLOC_SIZE;
		floor_texel.x = (int)(current_floor.x * w->texture[T_FLOOR].size.x) % w->texture[T_FLOOR].size.x;
		floor_texel.y = (int)(current_floor.y * w->texture[T_FLOOR].size.y) % w->texture[T_FLOOR].size.y;
		printf("%d - %d\n", floor_texel.x, floor_texel.y);
		put_pixel_from_txt(start, floor_texel, &w->texture[T_FLOOR], img);
		start.y++;
	}
*/
	double ratio;
	double perpDist;
	while (start.y < img->size.y)
	{
		ratio = w->cam.heightView / (start.y - (img->size.y / 2));
		perpDist = (fabs(w->cam.screenDist) * ratio);
		floor_texel.x = perpDist / d_cos(w->cam.ray_dir[start.x]);
		floor_texel.y = perpDist / d_sin(w->cam.ray_dir[start.x]);
		put_pixel_from_txt(start, floor_texel, &w->texture[T_FLOOR], img);
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
