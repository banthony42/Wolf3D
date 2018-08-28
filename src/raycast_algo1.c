/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_algo1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:47:42 by banthony          #+#    #+#             */
/*   Updated: 2018/08/28 20:07:01 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Calcul du point correspondant dans la map
**	Si le point est bien dans la map
**	Et qu'il touche un objet a afficher (murs, portes, etc)
**	On arrondit le point, pour pouvoir utiliser le modulo
**	On enregistre le point dans hit_point
**	On return la texture a afficher
**	Si l'option debug existe, alors on trace le point du rayon
**	(visualisation du trace de rayon, (FOV))
*/

static t_texture	find_intersection(t_wolf *w, t_vector a,
										t_vector *hit_point, int debug)
{
	t_coord		map;

	map.x = (int)(a.x / BLOC_SIZE);
	map.y = (int)(a.y / BLOC_SIZE);
	if (map.x < w->map_size.x && map.y < w->map_size.y)
	{
		if (w->map[map.y][map.x] > '0' && w->map[map.y][map.x] < '0' + T_DOOR + 1)
		{
			if ((int)(fmod(a.x, BLOC_SIZE)) == (int)(fmod(a.y, BLOC_SIZE)))
			{
				if (((int)(fmod(a.x, BLOC_SIZE)) == BLOC_SIZE - 1))
				{
					a.y = (int)(a.y + 1);
					a.x = (int)(a.x + 1);
				}
			}
			else if (fmod(a.x, BLOC_SIZE) < fmod(a.y, BLOC_SIZE))
				a.y = (int)(a.y + 1);
			else
				a.x = (int)(a.x + 1);
			*hit_point = a;
			return ((t_texture)(w->map[map.y][map.x] - '0'));
		}
		else if (debug)
			put_pixel_img((t_coord){(int)a.x, (int)a.y, 0}, RED, &w->img[GAME]);
	}
	return (0);
}

/*
**	Algo de trace de ligne DDA
**	Pour chaque point on verifie si il y a intersection avec un objet
**	dans la map. Si une intersection est trouve on stop le tracage.
*/

static t_texture	raycast(t_wolf *w, t_vector a, t_vector b,
										t_vector *hit_point)
{
	double		delta;
	int			i;
	t_vector	step;
	t_texture	texture;

	delta = fabs(b.y - a.y);
	if (fabs(b.x - a.x) >= delta)
		delta = fabs(b.x - a.x);
	step.x = (double)((b.x - a.x) / (double)delta);
	step.y = (double)((b.y - a.y) / (double)delta);
	i = -1;
	delta *= 2;
	while (++i < delta)
	{
		if ((texture = find_intersection(w, a, hit_point, 0)))
			return (texture);
		if (i % 2)
			a.x += step.x;
		else
			a.y += step.y;
	}
	return (0);
}

/*
**	Pour chaque colonne de pixel de l'ecran:
**	Calcul du point d'arrive du rayon (end)
**	Lancer du rayon via la fonction raycast
**	Recuperation des infos recu, dans la structure hit_info
**	Calcul de la distance reelle et projete du rayon, real_dist & dist
**	Calcul de la hauteur du mur en fonction de cette distance, (h_wall)
**	Enregistrement de quel axe a ete touche, x ou y (side)
**	Enregistrement de la texture a afficher
*/

void				launch_raycast_1(t_wolf *w)
{
	t_vector	end;
	t_texture	text;
	int			i;

	i = -1;
	while (++i < WIN_W)
	{
		end.x = (w->cam.pos.x - (w->cam.lengthView *
				d_cos(w->cam.pos.angle + w->cam.ray_dir[i])));
		end.y = (w->cam.pos.y - (w->cam.lengthView *
				d_sin(w->cam.pos.angle + w->cam.ray_dir[i])));
		if ((text = raycast(w, w->cam.pos, end, &w->hit[i].point)))
		{
			w->hit[i].real_dist = sqrt(((w->hit[i].point.y - w->cam.pos.y)
									* (w->hit[i].point.y - w->cam.pos.y))
									+ ((w->hit[i].point.x - w->cam.pos.x)
									* (w->hit[i].point.x - w->cam.pos.x)));
			w->hit[i].dist = d_cos(w->cam.ray_dir[i]) * w->hit[i].real_dist;
			w->hit[i].h_wall = (BLOC_SIZE / w->hit[i].dist) * w->cam.screenDist;
			w->hit[i].side = w->hit[i].point.y;
			if (((int)(w->hit[i].point.y) % BLOC_SIZE) == 0)
				w->hit[i].side = w->hit[i].point.x;
			w->hit[i].object = w->texture[text];
		}
	}
}
