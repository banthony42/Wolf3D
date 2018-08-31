/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:42:07 by banthony          #+#    #+#             */
/*   Updated: 2018/08/31 19:46:49 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			eventk_game(int keyhook, void *wolf)
{
	t_wolf		*w;
	t_vector	pt;
	t_door		*door;
	t_coord		cam_pos;

	ft_bzero(&pt, sizeof(pt));
	if (!(w = (t_wolf*)wolf))
		return (0);
	if (keyhook == MLX_KEY_ESCAPE)
		w->current_page = MAIN_MENU;
	if (keyhook == MLX_KEY_F1)
		w->textured = !w->textured;
	if (keyhook == MLX_KEY_SPACEBAR && w->cam.heightView <= (double)(WIN_H / 2))
		w->cam.velocity = JUMP_VELOCITY;
	if (w->keypress[KEY_C])
		w->cam.heightView = WIN_H / 2.8;
	if (w->keypress[KEY_RIGHT])
		w->cam.pos.angle += w->cam.spd_angle * w->time.delta;
	if (w->keypress[KEY_LEFT])
		w->cam.pos.angle -= w->cam.spd_angle * w->time.delta;
	if (w->keypress[KEY_W])
		move(w, FORWARD);
	if (w->keypress[KEY_S])
		move(w, BEHIND);
	if (w->keypress[KEY_D])
		move(w, RIGHT);
	if (w->keypress[KEY_A])
		move(w, LEFT);
	if (keyhook == MLX_KEY_E)
	{
		cam_pos.x = (int)(w->cam.pos.x / BLOC_SIZE);
		cam_pos.y = (int)(w->cam.pos.y / BLOC_SIZE);
		if (w->map[cam_pos.y][cam_pos.x] != '0' + T_DOOR)
		{
			pt.x = w->cam.pos.x - (w->cos_table[(int)w->cam.pos.angle] * USE_DIST);
			pt.y = w->cam.pos.y - (w->sin_table[(int)w->cam.pos.angle] * USE_DIST);
			if ((door = get_door(w, pt, 0, 0)))
				door->incr *= -1;
		}
	}
	launch_raycast_1(w);
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

static void	update_doors(t_wolf *w, int i)
{
	if (w->doors[i].timer > 1.0)
		w->doors[i].timer = 1.0;
	else if (w->doors[i].timer < 0.0)
		w->doors[i].timer = 0.0;
	if ((w->doors[i].timer >= 0.0) && (w->doors[i].timer <= 1.0))
	{
		if ((w->doors[i].incr > 0.0) && (w->doors[i].timer != 1.0))
			w->doors[i].timer += w->doors[i].incr * 0.02;
		else if ((w->doors[i].incr < 0.0) && (w->doors[i].timer != 0.0))
			w->doors[i].timer += w->doors[i].incr * 0.02;
	}
}

void		draw_game(void *wolf)
{
	t_wolf	*w;
	int		i;

	i = -1;
	if (!(w = (t_wolf*)wolf))
		return ;
	if (!w->keypress[KEY_C])
	{
		w->cam.heightView = w->cam.heightView + (w->cam.velocity * w->time.delta);
		if (w->cam.heightView > (WIN_H / 2))
			w->cam.velocity  = w->cam.velocity - GRAVITY * w->time.delta;
		else
			w->cam.heightView = WIN_H /2;
	}
	while (++i < MAX_DOOR)
		update_doors(w, i);
	renderer(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME].ptr, 0, 0);
}






