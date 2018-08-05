/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:42:07 by banthony          #+#    #+#             */
/*   Updated: 2018/08/05 20:10:38 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static double	to_radian(double degree)
{
	return (M_PI / 180 * degree);
}

static double	d_cos(double degree)
{
	return (cos(to_radian(degree)));
}

static double	d_sin(double degree)
{
	return (sin(to_radian(degree)));
}

/*
**	Tableau de fonction avec une fonction associe pour chaque touches
**	pour eviter les if sur les touches
*/
int			eventk_game(int keyhook, void *wolf)
{
	t_wolf	*w;
	t_coord	pt;

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
	{
		w->player.pos.x -= d_cos(w->player.pos.angle) * w->player.spd_move * w->time.delta;
		w->player.pos.y -= d_sin(w->player.pos.angle) * w->player.spd_move * w->time.delta;
	}
	if (w->keypress[KEY_S])
	{
		w->player.pos.x += d_cos(w->player.pos.angle) * w->player.spd_move * w->time.delta;
		w->player.pos.y += d_sin(w->player.pos.angle) * w->player.spd_move * w->time.delta;
	}
	if (w->keypress[KEY_D])
	{
		w->player.pos.x -= d_cos(w->player.pos.angle + 90) * w->player.spd_move * w->time.delta;
		w->player.pos.y -= d_sin(w->player.pos.angle + 90) * w->player.spd_move * w->time.delta;
	}
	if (w->keypress[KEY_A])
	{
		w->player.pos.x += d_cos(w->player.pos.angle + 90) * w->player.spd_move * w->time.delta;
		w->player.pos.y += d_sin(w->player.pos.angle + 90) * w->player.spd_move * w->time.delta;
	}
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

static void raycast(t_wolf *w)
{
	t_coord start;
	t_coord end;
	double lenght;
	int bloc_size;
	int i;
	double incr;

	bloc_size = 64;
	draw_landmark(&w->img[GAME]);
	lenght = (double)(-8 * bloc_size);
	incr = ((double)FOV / (double)WIN_W);
	start.color = GREEN;
	end.color = GREEN;
	i = -1;
	start.x = (int)(w->player.pos.x);
	start.y = (int)(w->player.pos.y);
	// FOV tracing
	while (++i < WIN_W)
	{
		end.x = (int)(w->player.pos.x + (lenght * d_cos((w->player.pos.angle + FOV / 2) - (i * incr))));
		end.y = (int)(w->player.pos.y + (lenght * d_sin((w->player.pos.angle + FOV / 2) - (i * incr))));
		draw_line_img(&w->img[GAME], &start, &end);
	}
	// CAM direction tracing
	start.color = BLUE;
	end.x = (int)(w->player.pos.x + (-200.0 * d_cos(w->player.pos.angle)));
	end.y = (int)(w->player.pos.y + (-200.0 * d_sin(w->player.pos.angle)));
	draw_line_img(&w->img[GAME], &start, &end);
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
