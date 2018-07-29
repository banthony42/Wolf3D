/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:42:07 by banthony          #+#    #+#             */
/*   Updated: 2018/07/29 18:55:58 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			eventk_game(int keyhook, void *wolf)
{
	t_wolf	*w;
	t_coord	pt;

	ft_bzero(&pt, sizeof(pt));
	if (!(w = (t_wolf*)wolf))
		return (0);
	if (keyhook == MLX_KEY_ESCAPE)
		w->current_page = MAIN_MENU;
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

static void	trace_map(t_wolf *w, t_coord i, int color)
{
	t_coord	n;
	t_coord	pt;
	t_coord	start;
	int		pitch;

	if (w->map_size.x > w->map_size.y)
		pitch = PERCENTAGE(90, MAPI_W) / MAP_MAX;
	else
		pitch = PERCENTAGE(90, MAPI_H) / MAP_MAX;
	start.x = CENTERMAPI_W(w->map_size.x * pitch);
	start.y = CENTERMAPI_H(w->map_size.y * pitch);
	pt.y = start.y + (i.y * pitch);
	n.y = -1;
	while (++n.y <= pitch)
	{
		pt.x = (start.x) + (i.x * pitch);
		n.x = -1;
		while (++n.x <= pitch)
		{
			if (!n.x || !n.y || n.x == pitch || n.y == pitch)
				put_pixel_img(pt, color, &w->img[MAP_I]);
			pt.x++;
		}
		pt.y++;
	}
}

static void	draw_map_overlay(t_wolf *w)
{
	t_coord i;

	fill_img(&w->img[MAP_I], MAP_OVERLAY);
	draw_landmark(&w->img[MAP_I]);
	i.y = -1;
	while (w->map[++i.y])
	{
		i.x = -1;
		while (w->map[i.y][++i.x])
		{
			if (w->map[i.y][i.x] > (T_VOID + '0'))
			{
				if (w->map[i.y][i.x] < (T_SPAWN + '0'))
				{
					if (w->map[i.y][i.x] == T_WOOD + '0')
						trace_map(w, i, BROWN);
					else if (w->map[i.y][i.x] == T_METAL + '0')
						trace_map(w, i, DARK_GREY);
					else
						trace_map(w, i, 0xe1ffe1);
				}
			}
		}
	}
}

void		draw_game(void *wolf)
{
	t_wolf	*w;
	t_coord	pt;

	if (!(w = (t_wolf*)wolf))
		return ;
	fill_img(&w->img[GAME], 0x111111);
	fill_img(&w->img[GAME_I], 0x2f2f2f);
	draw_map_overlay(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME].ptr, 0, 0);
	pt.x = 0;
	pt.y = w->img[GAME].size.y;
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME_I].ptr, pt.x, pt.y);
	pt.x = 100;
	pt.y = 100;
	string_to_img("Game Work in progress ...", pt, &w->img[GAME], w);
	pt.x = 16;
	pt.y = 32;
	string_to_img("Interface Work in progress ...", pt, &w->img[GAME_I], w);
}
