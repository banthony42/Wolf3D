/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:42:07 by banthony          #+#    #+#             */
/*   Updated: 2018/04/18 19:54:57 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		eventk_game(int keyhook, void *wolf)
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

int		eventm_game(int button, int x, int y, void *wolf)
{
	(void)wolf;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}


static void trace_map(t_wolf *w, t_coord i, char wall)
{
	t_coord n;
	t_coord	pt;
	int		color;
	t_coord start;
	int		 pitch;

	ft_bzero(&n, sizeof(n));
	color = 0xe1ffe1;
	if (wall == T_WOOD + '0')
		color = BROWN;
	if (wall == T_METAL + '0')
		color = DARK_GREY;

	if (w->map_size.x > w->map_size.y)
		pitch = PERCENTAGE(90, MAPI_W) / MAP_MAX;
	else
		pitch = PERCENTAGE(90, MAPI_H) / MAP_MAX;

	start.x = CENTERMAPI_W(w->map_size.x * pitch);
	start.y = CENTERMAPI_H(w->map_size.y * pitch);
	pt.y = start.y + (i.y * pitch);
	while (n.y <= pitch)
	{
		pt.x = (start.x) + (i.x * pitch);
		n.x = 0;
		while (n.x <= pitch)
		{
			if (!n.x || !n.y || n.x == pitch || n.y == pitch)
				put_pixel_img(pt, color, &w->img[MAP_I]);
			n.x++;
			pt.x++;
		}
		n.y++;
		pt.y++;
	}
}

static void	draw_map_overlay(t_wolf *w)
{
	t_coord i;
	t_coord size;

	ft_bzero(&i, sizeof(i));
	fill_img(&w->img[MAP_I], MAP_OVERLAY);
	draw_grid(&w->img[MAP_I]);
	size.y = (int)ft_tablen(w->map);
	while (w->map[i.y])
	{
		i.x = 0;
		while (w->map[i.y][i.x])
		{
			size.x = (int)ft_strlen(w->map[i.y]);
			if (w->map[i.y][i.x] > (T_VOID + '0') && w->map[i.y][i.x] < (T_SPAWN + '0'))
				trace_map(w, i, w->map[i.y][i.x]);
			i.x++;
		}
		i.y++;
	}
}

void	draw_game(void *wolf)
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

/*
	if (w->map_size.x > w->map_size.y)
		pitch = PERCENTAGE( ( 100 - ( 100 / (MAP_MAX / w->map_size.x))), MAPI_W) / MAP_MAX;
	else
		pitch = PERCENTAGE( ( 100 - ( 100 / (MAP_MAX / w->map_size.y))), MAPI_H) / MAP_MAX;
*/
//	draw_grid(&w->img[GAME]);
//	draw_grid(&w->img[GAME_I]);

/*
static void trace_map(t_wolf *w, t_coord i, t_coord size)
{
	t_coord	pt_a;
	t_coord pt_b;

	pt_a.color = 0xff0000;
	if (i.x + 1 < size.x)
	{
		pt_a.x = (i.x * (PITCH + size.x)) + START_X;
		pt_b.x = ((i.x + 1) * (PITCH + size.x)) + START_X;
		pt_a.y = (i.y * (PITCH + size.y)) + START_Y;
		pt_b.y = (i.y * (PITCH + size.y)) + START_Y;
		pt_a.y -= WALL_THICKNESS;
		pt_b.y -= WALL_THICKNESS;
		if (w->map[i.y][i.x] != '0' && w->map[i.y][i.x + 1] != '0')
			draw_line_img(&w->img[MAP_I], &pt_a, &pt_b);
		pt_a.y += WALL_THICKNESS * 2;
		pt_b.y += WALL_THICKNESS * 2;
		if (w->map[i.y][i.x] != '0' && w->map[i.y][i.x + 1] != '0')
			draw_line_img(&w->img[MAP_I], &pt_a, &pt_b);
	}
	if (i.y + 1 < size.y)
	{
		pt_a.x = (i.x * (PITCH + size.x)) + START_X;
		pt_b.x = (i.x * (PITCH + size.x)) + START_X;
		pt_a.y = (i.y * (PITCH + size.y)) + START_Y;
		pt_b.y = ((i.y + 1) * (PITCH + size.y)) + START_Y;
		pt_a.x -= WALL_THICKNESS;
		pt_b.x -= WALL_THICKNESS;
		if (w->map[i.y][i.x] != '0' && w->map[i.y + 1][i.x] != '0')
			draw_line_img(&w->img[MAP_I], &pt_a, &pt_b);
		pt_a.x += WALL_THICKNESS * 2;
		pt_b.x += WALL_THICKNESS * 2;
		if (w->map[i.y][i.x] != '0' && w->map[i.y + 1][i.x] != '0')
			draw_line_img(&w->img[MAP_I], &pt_a, &pt_b);
	}
}*/
