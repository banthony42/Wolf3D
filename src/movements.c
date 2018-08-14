/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:00:24 by grdalmas          #+#    #+#             */
/*   Updated: 2018/08/14 17:23:59 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		check_collision(t_vector pt, t_wolf *w)
{
	t_coord map;

	map.x = (int)(pt.x / BLOC_SIZE);
	map.y = (int)(pt.y / BLOC_SIZE);
	if (map.x > w->map_size.x || map.y > w->map_size.y)
		return (1);
	if (map.x < 0 || map.y < 0)
		return (1);
	if (w->map[map.y][map.x] > '0' && w->map[map.y][map.x] < ('0' + T_DOOR))
		return (1);
	return (0);
}

void	move_right(t_wolf *w)
{
	t_vector pt;

	pt = w->cam.pos;
	pt.x -= d_cos(w->cam.pos.angle + 90) * w->cam.spd_move * w->time.delta;
	if (!(check_collision(pt, w)))
		w->cam.pos = pt;
	pt.y -= d_sin(w->cam.pos.angle + 90) * w->cam.spd_move * w->time.delta;
	if (!(check_collision(pt, w)))
		w->cam.pos = pt;
}

void	move_left(t_wolf *w)
{
	t_vector pt;

	pt = w->cam.pos;
	pt.x += d_cos(w->cam.pos.angle + 90) * w->cam.spd_move * w->time.delta;
	if (!(check_collision(pt, w)))
		w->cam.pos = pt;
	pt.y += d_sin(w->cam.pos.angle + 90) * w->cam.spd_move * w->time.delta;
	if (!(check_collision(pt, w)))
		w->cam.pos = pt;
}

void	move_back(t_wolf *w)
{
	t_vector pt;

	pt = w->cam.pos;
	pt.x += d_cos(w->cam.pos.angle) * w->cam.spd_move * w->time.delta;
	if (!(check_collision(pt, w)))
		w->cam.pos = pt;
	pt.y += d_sin(w->cam.pos.angle) * w->cam.spd_move * w->time.delta;
	if (!(check_collision(pt, w)))
		w->cam.pos = pt;
}

void	move_forward(t_wolf *w)
{
	t_vector pt;

	pt = w->cam.pos;
	pt.x -= d_cos(w->cam.pos.angle) * w->cam.spd_move * w->time.delta;
	if (!(check_collision(pt, w)))
		w->cam.pos = pt;
	pt.y -= d_sin(w->cam.pos.angle) * w->cam.spd_move * w->time.delta;
	if (!(check_collision(pt, w)))
		w->cam.pos = pt;
}
