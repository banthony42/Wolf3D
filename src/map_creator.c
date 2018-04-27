/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:58:11 by banthony          #+#    #+#             */
/*   Updated: 2018/04/27 17:08:40 by banthony         ###   ########.fr       */
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

static void	draw_interface(t_wolf *w)
{
	char *str = "< MAP CREATOR >";
	t_coord pt;

	pt.y = 100;
	pt.x = 100;
	string_to_img(str, centerx_str(str, pt), &w->img[MAP_CREATOR], w);
}

void	draw_map_creator(void *wolf)
{
	t_wolf	*w;

	if (!(w = (t_wolf*)wolf))
		return ;
	fill_img(&w->img[MAP_CREATOR], 0x311111);
	fill_img(&w->img[GAME_I], 0x2f2f2f);
	draw_grid(&w->img[MAP_CREATOR]);
	draw_grid(&w->img[GAME_I]);
	mlx_put_image_to_window(w->mlx, w->win, w->img[MAP_CREATOR].ptr, 0, 0);
	draw_interface(w);
}
