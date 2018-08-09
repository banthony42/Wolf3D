/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:00:24 by grdalmas          #+#    #+#             */
/*   Updated: 2018/08/09 19:17:30 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_right(t_wolf *w)
{
	t_vector pt;

	pt = w->player.pos;
	pt.x -= d_cos(w->player.pos.angle + 90) * w->player.spd_move * w->time.delta;
	pt.y -= d_sin(w->player.pos.angle + 90) * w->player.spd_move * w->time.delta;
	if (((int)pt.x / 64) > w->map_size.x || ((int)pt.y / 64) > w->map_size.y)
		return;
	if (((int)pt.x / 64) < 0 || ((int)pt.y / 64) < 0)
		return;
	if (ft_strchr(WALL, w->map[(int)((int)pt.y / 64)][(int)((int)pt.x / 64)]))
		return;
	w->player.pos = pt;
}

void	move_left(t_wolf *w)
{
	t_vector pt;

	pt = w->player.pos;
	pt.x += d_cos(w->player.pos.angle + 90) * w->player.spd_move * w->time.delta;
	pt.y += d_sin(w->player.pos.angle + 90) * w->player.spd_move * w->time.delta;
	if (((int)pt.x / 64) > w->map_size.x || ((int)pt.y / 64) > w->map_size.y)
		return;
	if (((int)pt.x / 64) < 0 || ((int)pt.y / 64) < 0)
		return;
	if (ft_strchr(WALL, w->map[(int)((int)pt.y / 64)][(int)((int)pt.x / 64)]))
		return;
	w->player.pos = pt;
}

void	move_back(t_wolf *w)
{
	t_vector pt;

	pt = w->player.pos;
	pt.x += d_cos(w->player.pos.angle) * w->player.spd_move * w->time.delta;
	pt.y += d_sin(w->player.pos.angle) * w->player.spd_move * w->time.delta;
	if (((int)pt.x / 64) > w->map_size.x || ((int)pt.y / 64) > w->map_size.y)
		return;
	if (((int)pt.x / 64) < 0 || ((int)pt.y / 64) < 0)
		return;
	if (ft_strchr(WALL, w->map[(int)((int)pt.y / 64)][(int)((int)pt.x / 64)]))
		return;
	w->player.pos = pt;
}

void	move_forward(t_wolf *w)
{
	t_vector pt;

	pt = w->player.pos;
	pt.x -= d_cos(w->player.pos.angle) * w->player.spd_move * w->time.delta;
	pt.y -= d_sin(w->player.pos.angle) * w->player.spd_move * w->time.delta;
	if (((int)pt.x / 64) > w->map_size.x || ((int)pt.y / 64) > w->map_size.y)
		return;
	if (((int)pt.x / 64) < 0 || ((int)pt.y / 64) < 0)
		return;
	if (ft_strchr(WALL, w->map[(int)((int)pt.y / 64)][(int)((int)pt.x / 64)]))
		return;
	w->player.pos = pt;
}

#if 0
static void	right(t_wolf *w)
{
	(void)w;
}

static void	left(t_wolf *w)
{
	(void)w;
}

static void	horizontal_mv(int key, t_wolf *w)
{
	(void)w;
	(void)key;
}

static void	lateral_mv(int key, t_wolf *w)
{
	(void)w;
	(void)key;
}

/*
** Creation de fonction de mouvement (Deso je savais pas pas quoi commencer xD)
*/

static void	player_move(int key, t_wolf *w)
{
	horizontal_mv(key, w);
	lateral_mv(key, w);
	if (key == MLX_KEY_PAD_4)
		left(w); // a coder
	if (key == MLX_KEY_PAD_6)
		right(w); // a coder
	if (key == MLX_KEY_SPACEBAR)
		;//variable saut a reflechir genre jump != jump a creuser
	if (key == MLX_KEY_SHIFT_LEFT)
		;//variable sprint meme modele que jump
	if (key == MLX_KEY_ESCAPE)
	{
		mlx_destroy_window(w->mlx, w->win);
		exit(0);
	}
}

#endif
