/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:42:07 by banthony          #+#    #+#             */
/*   Updated: 2018/08/09 19:12:06 by banthony         ###   ########.fr       */
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
	if (w->keypress[KEY_RIGHT])
		w->player.pos.angle += w->player.spd_angle * w->time.delta;
	if (w->keypress[KEY_LEFT])
		w->player.pos.angle -= w->player.spd_angle * w->time.delta;
	if (w->keypress[KEY_W])
		move_forward(w);
	if (w->keypress[KEY_S])
		move_back(w);
	if (w->keypress[KEY_D])
		move_right(w);
	if (w->keypress[KEY_A])
		move_left(w);
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

static void intersect(t_wolf *w, t_coord a, t_coord b)
{
	int	delta;
	int i;
	t_vector step;
	t_vector pt_d;
	t_coord pt;

	delta = abs(b.y - a.y);
	if (abs(b.x - a.x) >= delta)
		delta = abs(b.x - a.x);
	step.x = ((double)b.x - (double)a.x) / (double)delta;
	step.y = ((double)b.y - (double)a.y) / (double)delta;
	pt_d = (t_vector){a.x + 0.5, a.y + 0.5, 0};
	i = -1;
	while (++i < delta)
	{
		pt = (t_coord){(int)pt_d.x, (int)pt_d.y, CLR};
		if ((pt.x / 64) < w->map_size.x && (pt.y / 64) < w->map_size.y)
		{
			if (ft_strchr(WALL, w->map[pt.y / 64][pt.x / 64]))
				return ;
		}
		put_pixel_img(pt, RED, &w->img[GAME]);
		pt_d.x += step.x;
		pt_d.y += step.y;
	}
}

static void raycast(t_wolf *w)
{
	t_coord start;
	t_coord end;
	int i;

	i = -1;
	start.x = (int)(w->player.pos.x);
	start.y = (int)(w->player.pos.y);
	// FOV tracing
	while (++i < WIN_W)
	{
		end.x = (int)(w->player.pos.x - (w->player.length *
								 d_cos((w->player.pos.angle + w->player.fov_half) - w->player.ray_dir[i])));
		end.y = (int)(w->player.pos.y - (w->player.length *
								 d_sin((w->player.pos.angle + w->player.fov_half) - w->player.ray_dir[i])));
		intersect(w, start, end);
	}
}

void		draw_game(void *wolf)
{
	t_wolf	*w;

	if (!(w = (t_wolf*)wolf))
		return ;
	fill_img(&w->img[MAP_I], MAP_OVERLAY);
	draw_map(w, w->map, w->map_size);
	raycast(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME].ptr, 0, 0);
}
