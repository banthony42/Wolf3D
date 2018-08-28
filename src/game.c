/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:42:07 by banthony          #+#    #+#             */
/*   Updated: 2018/08/28 13:05:30 by banthony         ###   ########.fr       */
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
	renderer(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME].ptr, 0, 0);
}
