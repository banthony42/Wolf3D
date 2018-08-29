/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:42:07 by banthony          #+#    #+#             */
/*   Updated: 2018/08/29 02:01:37 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			eventk_game(int keyhook, void *wolf)
{
	t_wolf		*w;
	t_vector	pt;

	ft_bzero(&pt, sizeof(pt));
	if (!(w = (t_wolf*)wolf))
		return (0);
	if (keyhook == MLX_KEY_ESCAPE)
		w->current_page = MAIN_MENU;
	if (keyhook == MLX_KEY_F1)
		w->textured = !w->textured;
	if (keyhook == MLX_KEY_SPACEBAR && w->cam.heightView == WIN_H / 2)
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
	if (keyhook == MLX_KEY_P)
		w->door_timer = 1;
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

void		draw_game(void *wolf)
{
	t_wolf	*w;

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
	if (w->door_timer >= 0)
		w->door_timer -= w->time.delta;
	printf("t:%f\n", w->door_timer);
	renderer(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME].ptr, 0, 0);
}
