/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_algo1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:47:42 by banthony          #+#    #+#             */
/*   Updated: 2018/08/23 19:37:07 by grdalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

// RAYCASTER

/*
**	DDA pour tracer le rayon
**	Arrondit de la valeur de l'axe sur lequel le rayon touche, ligne: 102 / 104
**	Car sinon le modulo dans la fonction raycast ne fonctionne pas.
*/

static t_texture	find_intersection(t_wolf *w, t_vector a, t_vector b, t_vector *hit_point)
{
	double		delta;
	int			i;
	t_vector	step;
	t_coord		map_point;

	delta = fabs(b.y - a.y);
	if (fabs(b.x - a.x) >= delta)
		delta = fabs(b.x - a.x);
	step.x = (double)((b.x - a.x) / (double)delta);
	step.y = (double)((b.y - a.y) / (double)delta);
	i = -1;
	while (++i < delta)
	{
		map_point.x = ((int)a.x / BLOC_SIZE);
		map_point.y = ((int)a.y / BLOC_SIZE);
		if (map_point.x < w->map_size.x && map_point.y < w->map_size.y)
		{
			if (w->map[map_point.y][map_point.x] > '0' && w->map[map_point.y][map_point.x] < '0' + T_DOOR)
			{
				if (fmod(a.x, BLOC_SIZE) < fmod(a.y, BLOC_SIZE))
					a.y = (int)(a.y + 1);
				else
					a.x = (int)(a.x + 1);
				*hit_point = a;
				return ((t_texture)(w->map[map_point.y][map_point.x] - '0'));
			}
		}
		a.x += step.x;
		a.y += step.y;
	}
	return (0);
}

/*
**	NOTE:
**	Pour trouver l'orientation du mur, se baser sur la direction du rayon ?
**	Chute de fps enorme quand tout proche d'un mur = hauteur du mur plus grand que hauteur fenetre,
**	donc bcp de tour de boucle sont inutile quand on es proche d'un mur
**	Revoir les calculs pour les optimiser pour les perfs
**	Detection des collision dans movements.c a revoir
**
**	Calcul de la distance projete sur l'axe vertical (delta y)
**	dist = cos(angle:Vertical/Hypotenuse) x longueurHypotenuse
**	longueurHypotenuse calc avec pythagore
*/

// void				raycast_1(t_wolf *w)
// {
// 	t_vector	end;
// 	t_w->hit[i]_info	w->hit[i];
// 	double		h_wall;
// 	t_texture	text;
// 	int			i;

// 	i = -1;
// 	h_wall = 0;
// 	while (++i < WIN_W)
// 	{
// 		end.x = (w->cam.pos.x - (w->cam.lengthView *
// 				d_cos(w->cam.pos.angle + w->cam.ray_dir[i])));
// 		end.y = (w->cam.pos.y - (w->cam.lengthView *
// 				d_sin(w->cam.pos.angle + w->cam.ray_dir[i])));
// 		if ((text = find_intersection(w, w->cam.pos, end, &w->hit[i].point)))
// 		{
// 			w->hit[i].dist = d_cos(w->cam.ray_dir[i])
// 				* sqrt(((w->hit[i].point.y - w->cam.pos.y) * (w->hit[i].point.y - w->cam.pos.y))
// 				+ ((w->hit[i].point.x - w->cam.pos.x) * (w->hit[i].point.x - w->cam.pos.x)));
// 			h_wall = (BLOC_SIZE / w->hit[i].dist) * w->cam.screenDist;
// 			w->hit[i].side = w->hit[i].point.y;
// 			if (((int)(w->hit[i].point.y) % BLOC_SIZE) == 0)
// 				w->hit[i].side = w->hit[i].point.x;
// 			w->hit[i].object = w->texture[text];
// 			renderer(w, i, w->hit[i], h_wall);
// 		}
// 	}
// }

void				raycast_1(t_wolf *w)
{
	t_vector	end;
	double		h_wall;
	t_texture	text;
	int			i;

	i = -1;
	h_wall = 0;
	while (++i < WIN_W)
	{
		end.x = (w->cam.pos.x - (w->cam.lengthView *
				d_cos(w->cam.pos.angle + w->cam.ray_dir[i])));
		end.y = (w->cam.pos.y - (w->cam.lengthView *
				d_sin(w->cam.pos.angle + w->cam.ray_dir[i])));
		if ((text = find_intersection(w, w->cam.pos, end, &w->hit[i].point)))
		{
			w->hit[i].dist = d_cos(w->cam.ray_dir[i])
				* sqrt(((w->hit[i].point.y - w->cam.pos.y) * (w->hit[i].point.y - w->cam.pos.y))
				+ ((w->hit[i].point.x - w->cam.pos.x) * (w->hit[i].point.x - w->cam.pos.x)));
			h_wall = (BLOC_SIZE / w->hit[i].dist) * w->cam.screenDist;
			w->hit[i].side = w->hit[i].point.y;
			if (((int)(w->hit[i].point.y) % BLOC_SIZE) == 0)
				w->hit[i].side = w->hit[i].point.x;
			w->hit[i].object = w->texture[text];
			renderer(w, i, w->hit[i], h_wall);
		}
	}
}
