/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:42:07 by banthony          #+#    #+#             */
/*   Updated: 2018/08/04 21:57:41 by banthony         ###   ########.fr       */
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

void		draw_game(void *wolf)
{
	t_wolf	*w;
	t_coord	pt;

	if (!(w = (t_wolf*)wolf))
		return ;
	fill_img(&w->img[GAME], 0x111111);
	fill_img(&w->img[GAME_I], 0x2f2f2f);
	fill_img(&w->img[MAP_I], MAP_OVERLAY);
	draw_map(w, w->map, w->map_size);
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
