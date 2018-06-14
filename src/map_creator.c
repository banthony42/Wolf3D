/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:58:11 by banthony          #+#    #+#             */
/*   Updated: 2018/06/14 16:54:01 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		eventk_map_creator(int keyhook, void *wolf)
{
	t_wolf *w;

	if (!(w = (t_wolf*)wolf))
		return (0);
	if (keyhook == MLX_KEY_ESCAPE)
		w->current_page = MAIN_MENU;
	else if (keyhook == MLX_KEY_DOWN)
		(void)wolf;
	else if (keyhook == MLX_KEY_RIGHT)
		(void)wolf;
	else if (keyhook == MLX_KEY_UP)
		(void)wolf;
	else if (keyhook == MLX_KEY_LEFT)
		(void)wolf;
	return (0);
}

int		eventm_map_creator(int button, int x, int y, void *wolf)
{
	(void)wolf;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

static void draw_box(t_coord size, int x, int y, t_wolf *w)
{
	t_coord i;
	t_coord max;

	i.x = x;
	i.y = y;
	max.x = x + size.x;
	max.y = y + size.y;
	while (i.y < max.y)
	{
		i.x = x;
		while (i.x < max.x)
		{
			if (i.x == x || i.y == y || i.x == max.x - 1 || i.y == max.y - 1)
				put_pixel_img(i, 0xd4af37, &w->img[GAME_I]);
			i.x++;
		}
		i.y++;
	}
}

static void	draw_interface(t_wolf *w)
{
	char *title = "MAP CREATOR";
	char *info = "Draw your map";
	char *save = "save";

	t_coord pt;
	t_coord box_size;
	int n_box;
	int box_pitch;
	int i;

	i = 0;
	n_box = 5;
	box_pitch = 16;
	box_size.x = 48;
	box_size.y = 48;
	pt.color = 46;

	pt.x = PERCENTAGE(50, w->img[MAP_CREATOR].size.x);
	pt.y = PERCENTAGE(2, w->img[MAP_CREATOR].size.y);
	string_to_img(title, centerx_str(title, pt), &w->img[MAP_CREATOR], w);

	pt.x = PERCENTAGE(50, w->img[GAME_I].size.x);
	pt.y = PERCENTAGE(5, w->img[GAME_I].size.y);
	string_to_img(info, centerx_str(info, pt), &w->img[GAME_I], w);

	pt.y = PERCENTAGE(50, w->img[GAME_I].size.y);
	pt.x = (PERCENTAGE(50, w->img[GAME_I].size.x)) - ((n_box / 2) * (box_size.x + box_pitch));
	while (i < n_box)
	{
		draw_box(box_size, pt.x - 1, pt.y - 1, w);
		put_texture_on_img_at(&w->img[GAME_I], &w->texture[T_STONE + i], w, pt);
		pt.x += box_size.x + box_pitch;
		i++;
	}
	box_size.y = 50;
	box_size.x = (int)(ft_strlen(save) * 32);
	pt.x = PERCENTAGE(80, w->img[GAME_I].size.x);
	draw_box(box_size, pt.x, pt.y, w);
	pt.x += (box_size.x / 2) + 7;
	pt.y += 2;
	string_to_img(save, centerx_str(save, pt), &w->img[GAME_I], w);
}

void	draw_map_creator(void *wolf)
{
	t_wolf	*w;

	if (!(w = (t_wolf*)wolf))
		return ;
	fill_img(&w->img[MAP_I], 0x2f2f2f);
	put_texture_on_img(&w->img[MAP_CREATOR], &w->texture[T_MAP_CREATOR], w);
	put_texture_on_img(&w->img[GAME_I], &w->texture[T_CREATOR_INTERFACE], w);
	mlx_put_image_to_window(w->mlx, w->win, w->img[MAP_CREATOR].ptr, 0, 0);
	mlx_put_image_to_window(w->mlx, w->win, w->img[MAP_I].ptr, (SCREEN_W - MAPI_W) / 2, (SCREEN_H - MAPI_H) / 2);
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME_I].ptr, 0, w->img[GAME].size.y);
	draw_interface(w);
}
