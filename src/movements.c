/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:00:24 by grdalmas          #+#    #+#             */
/*   Updated: 2018/08/31 19:44:35 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				check_collision(t_vector pt, t_wolf *w, int hitbox_radius)
{
	t_coord		new_map;
	t_vector	new_pt;
	t_door		*door;
	int			i;

	i = -1;
	while (++i < 360)
	{
		new_pt.x = pt.x + (w->cos_table[i] * hitbox_radius);
		new_pt.y = pt.y + (w->sin_table[i] * hitbox_radius);
		new_map.x = (int)(new_pt.x / BLOC_SIZE);
		new_map.y = (int)(new_pt.y / BLOC_SIZE);
		if (new_map.x >= w->map_size.x || new_map.y >= w->map_size.y)
			return (1);
		if (new_map.x < 0 || new_map.y < 0)
			return (1);
		if (w->map[new_map.y][new_map.x] > '0' && w->map[new_map.y][new_map.x] < ('0' + T_DOOR))
			return (1);
		if (w->map[new_map.y][new_map.x] == '0' + T_DOOR && (door = get_door(w, pt, 0, 0)))
			if (door->timer < 1)
				return (1);
	}
	return (0);
}

void			move(t_wolf *w, int dir)
{
	t_vector	pt;
	double		move_x;
	double		move_y;

	move_x = d_cos(w->cam.pos.angle + dir) * w->cam.spd_move * w->time.delta;
	move_y = d_sin(w->cam.pos.angle + dir) * w->cam.spd_move * w->time.delta;
	pt = w->cam.pos;
	pt.x -= move_x;
	if (!(check_collision(pt, w, PLAYER_RADIUS)))
		w->cam.pos.x -= move_x;
	else
		pt = w->cam.pos;
	pt.y -= move_y;
	if (!(check_collision(pt, w, PLAYER_RADIUS)))
		w->cam.pos.y -= move_y;
}
